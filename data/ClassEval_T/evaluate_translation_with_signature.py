"""
Evaluate ClassEval-T translation tasks (raw vs signature-converted).

Default behavior (no args):
- Input root: /Users/bytedance/XLLM_COT/data/derived_cot/rq3_early_stopping/output/qwen/translation
- Evaluate all translation tasks under that root:
  - cpp_to_py
  - java_to_py
  - py_to_cpp
  - java_to_cpp
- Output:
  - /mnt/sda/yz/projects/XLLM_COT/data/derived_cot/rq2_eval/translation/r1/result_raw.json
  - /mnt/sda/yz/projects/XLLM_COT/data/derived_cot/rq2_eval/translation/r1/result_converted.json
  - /mnt/sda/yz/projects/XLLM_COT/data/derived_cot/rq2_eval/translation/r1/result.json

Result JSON format follows data/derived_cot/rq2_eval/execution/*/result.json style:
{
  "total": ...,
  "passed": ...,
  "failed": ...,
  "results": [{"task_id": "...", "failed": 0/1, ...}, ...]
}
"""

import argparse
import json
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from signature_converter.converter import convert_file as convert_py_file
from signature_converter.cpp_converter import convert_cpp_file

DEFAULT_TRANSLATION_ROOT = Path("/Users/bytedance/XLLM_COT/data/derived_cot/rq3_early_stopping/output/qwen/translation")
DEFAULT_OUTPUT_DIR = Path("/Users/bytedance/XLLM_COT/data/derived_cot/rq3_early_stopping/eval/translation/qwen")
SUPPORTED_TASKS = ["cpp_to_py", "java_to_py", "py_to_cpp", "java_to_cpp"]


PY_TEST_WORKER = r"""
import io
import json
import os
import sys
import unittest

solution_file = sys.argv[1]
test_file = sys.argv[2]
temp_dir = sys.argv[3]

def extract_first_error(result):
    if result.failures:
        _, trace = result.failures[0]
        if trace:
            lines = trace.strip().split("\n")
            return lines[-1][:200] if lines else ""
    if result.errors:
        _, trace = result.errors[0]
        if trace:
            lines = trace.strip().split("\n")
            return lines[-1][:200] if lines else ""
    return ""

original_dir = os.getcwd()
try:
    os.chdir(temp_dir)
    namespace = {"__name__": "__main__", "unittest": unittest}
    with open(solution_file, "r", encoding="utf-8") as f:
        solution_code = f.read()
    with open(test_file, "r", encoding="utf-8") as f:
        test_code = f.read()
    exec(solution_code, namespace)
    exec(test_code, namespace)

    loader = unittest.TestLoader()
    suite = unittest.TestSuite()
    for _, obj in namespace.items():
        if isinstance(obj, type) and issubclass(obj, unittest.TestCase) and obj is not unittest.TestCase:
            suite.addTests(loader.loadTestsFromTestCase(obj))

    stream = io.StringIO()
    runner = unittest.TextTestRunner(stream=stream, verbosity=0)
    result = runner.run(suite)

    total = result.testsRun
    failed = len(result.failures) + len(result.errors)
    passed = total - failed
    payload = {"total": total, "passed": passed, "failed": failed, "error": extract_first_error(result)}
    print(json.dumps(payload, ensure_ascii=False))
except Exception as exc:
    print(json.dumps({"total": 0, "passed": 0, "failed": 0, "error": f"{type(exc).__name__}: {str(exc)[:200]}"}, ensure_ascii=False))
finally:
    try:
        os.chdir(original_dir)
    except Exception:
        pass
"""


CPP_PREAMBLE = """
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <stack>
#include <queue>
#include <functional>
#include <regex>
#include <chrono>
#include <iomanip>
#include <numeric>
#include <memory>
#include <stdexcept>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;
"""


def parse_last_json_line(text: str) -> Optional[Dict[str, object]]:
    for line in reversed(text.splitlines()):
        line = line.strip()
        if not line:
            continue
        try:
            payload = json.loads(line)
            if isinstance(payload, dict):
                return payload
        except json.JSONDecodeError:
            continue
    return None


def list_task_dirs(translation_root: Path) -> List[Tuple[str, Path]]:
    task_dirs = []
    for task in SUPPORTED_TASKS:
        code_dir = translation_root / task / "code_output"
        if code_dir.exists():
            task_dirs.append((task, code_dir))
    return task_dirs


def evaluate_python_file(solution_file: Path, test_file: Path, timeout_sec: int) -> Dict[str, object]:
    if not solution_file.exists():
        return {"failed": 1, "total": 0, "passed": 0, "error": "Solution file not found"}
    if not test_file.exists():
        return {"failed": 1, "total": 0, "passed": 0, "error": "Test file not found"}

    temp_dir = tempfile.mkdtemp(prefix="classeval_py_")
    try:
        proc = subprocess.run(
            [sys.executable, "-c", PY_TEST_WORKER, str(solution_file), str(test_file), temp_dir],
            capture_output=True,
            text=True,
            timeout=timeout_sec,
            check=False,
        )
    except subprocess.TimeoutExpired:
        return {"failed": 1, "total": 0, "passed": 0, "error": f"timeout>{timeout_sec}s"}
    finally:
        shutil.rmtree(temp_dir, ignore_errors=True)

    payload = parse_last_json_line(proc.stdout)
    if payload is None:
        stderr = (proc.stderr or "").strip().splitlines()
        error = stderr[-1][:180] if stderr else "Worker returned no JSON"
        return {"failed": 1, "total": 0, "passed": 0, "error": error}

    total = int(payload.get("total", 0))
    passed = int(payload.get("passed", 0))
    failed_tests = int(payload.get("failed", 0))
    error = str(payload.get("error", ""))
    task_failed = 0 if (total > 0 and failed_tests == 0) else 1
    if total == 0 and not error:
        error = "No tests discovered"
    return {"failed": task_failed, "total": total, "passed": passed, "error": error}


def extract_first_compile_error(stderr: str) -> str:
    for line in stderr.splitlines():
        if "error:" in line:
            return line.split("error:", 1)[-1].strip()[:200]
    return stderr.strip().splitlines()[-1][:200] if stderr.strip() else ""


def evaluate_cpp_file(solution_file: Path, timeout_sec: int) -> Dict[str, object]:
    if not solution_file.exists():
        return {"failed": 1, "total": 1, "passed": 0, "error": "Solution file not found"}

    try:
        solution_code = solution_file.read_text(encoding="utf-8")
    except Exception as exc:  # noqa: BLE001
        return {"failed": 1, "total": 1, "passed": 0, "error": f"ReadError: {type(exc).__name__}"}

    temp_dir = tempfile.mkdtemp(prefix="classeval_cpp_")
    temp_source = Path(temp_dir) / solution_file.name
    temp_obj = Path(temp_dir) / f"{solution_file.stem}.o"
    full_code = CPP_PREAMBLE + solution_code + "\nint main() { return 0; }\n"

    try:
        temp_source.write_text(full_code, encoding="utf-8")
        proc = subprocess.run(
            ["g++", "-std=c++17", "-c", str(temp_source), "-o", str(temp_obj)],
            capture_output=True,
            text=True,
            timeout=timeout_sec,
            check=False,
        )
    except subprocess.TimeoutExpired:
        return {"failed": 1, "total": 1, "passed": 0, "error": f"compile timeout>{timeout_sec}s"}
    except FileNotFoundError:
        return {"failed": 1, "total": 1, "passed": 0, "error": "g++ not found"}
    finally:
        shutil.rmtree(temp_dir, ignore_errors=True)

    if proc.returncode == 0:
        return {"failed": 0, "total": 1, "passed": 1, "error": ""}
    return {"failed": 1, "total": 1, "passed": 0, "error": extract_first_compile_error(proc.stderr)}


def evaluate_direction(direction: str, code_dir: Path, py_test_dir: Path, timeout_sec: int) -> List[Dict[str, object]]:
    results: List[Dict[str, object]] = []
    is_to_py = direction.endswith("_to_py")
    ext = ".py" if is_to_py else ".cpp"
    files = sorted(code_dir.glob(f"*{ext}"))

    prefix = f"{direction}_"
    for file_path in files:
        stem = file_path.stem
        class_name = stem[len(prefix):] if stem.startswith(prefix) else stem
        task_id = f"{direction}/{class_name}"
        if is_to_py:
            test_file = py_test_dir / f"{class_name}.py"
            outcome = evaluate_python_file(file_path, test_file, timeout_sec)
        else:
            outcome = evaluate_cpp_file(file_path, timeout_sec)

        results.append(
            {
                "task_id": task_id,
                "failed": int(outcome["failed"]),
                "total": int(outcome["total"]),
                "passed": int(outcome["passed"]),
                "direction": direction,
                "error": str(outcome.get("error", "")),
            }
        )
    return results


def convert_direction(
    direction: str,
    raw_dir: Path,
    converted_dir: Path,
    py_target_dir: Path,
    cpp_target_dir: Path,
    threshold: float,
) -> None:
    converted_dir.mkdir(parents=True, exist_ok=True)
    is_to_py = direction.endswith("_to_py")
    ext = ".py" if is_to_py else ".cpp"

    for src in sorted(raw_dir.glob(f"*{ext}")):
        dst = converted_dir / src.name
        if is_to_py:
            target = py_target_dir / src.name
            if not target.exists():
                shutil.copy2(src, dst)
                continue
            try:
                convert_py_file(str(src), str(target), str(dst), threshold)
            except Exception:  # noqa: BLE001
                shutil.copy2(src, dst)
        else:
            target = cpp_target_dir / src.name
            if not target.exists():
                shutil.copy2(src, dst)
                continue
            try:
                convert_cpp_file(str(src), str(target), str(dst), threshold)
            except Exception:  # noqa: BLE001
                shutil.copy2(src, dst)


def summarize_results(items: List[Dict[str, object]]) -> Dict[str, object]:
    total = len(items)
    passed = sum(1 for item in items if int(item["failed"]) == 0)
    failed = total - passed
    return {"total": total, "passed": passed, "failed": failed, "results": items}


def build_union_results(raw_items: List[Dict[str, object]], converted_items: List[Dict[str, object]]) -> Dict[str, object]:
    raw_map = {item["task_id"]: item for item in raw_items}
    converted_map = {item["task_id"]: item for item in converted_items}
    task_ids = sorted(set(raw_map.keys()) | set(converted_map.keys()))

    merged: List[Dict[str, object]] = []
    for task_id in task_ids:
        raw = raw_map.get(task_id)
        conv = converted_map.get(task_id)

        raw_failed = int(raw["failed"]) if raw else 1
        conv_failed = int(conv["failed"]) if conv else 1
        final_failed = 0 if (raw_failed == 0 or conv_failed == 0) else 1

        direction = ""
        if raw and raw.get("direction"):
            direction = str(raw["direction"])
        elif conv and conv.get("direction"):
            direction = str(conv["direction"])

        raw_total = int(raw.get("total", 0)) if raw else 0
        conv_total = int(conv.get("total", 0)) if conv else 0
        total = max(raw_total, conv_total)

        raw_passed = int(raw.get("passed", 0)) if raw else 0
        conv_passed = int(conv.get("passed", 0)) if conv else 0
        if final_failed == 0:
            passed = total if total > 0 else max(raw_passed, conv_passed)
        else:
            passed = max(raw_passed, conv_passed)

        error = ""
        if final_failed == 1:
            raw_error = str(raw.get("error", "")) if raw else ""
            conv_error = str(conv.get("error", "")) if conv else ""
            error = f"raw: {raw_error} | converted: {conv_error}"[:300]

        merged.append(
            {
                "task_id": task_id,
                "failed": final_failed,
                "total": total,
                "passed": passed,
                "direction": direction,
                "error": error,
                "raw_failed": raw_failed,
                "converted_failed": conv_failed,
            }
        )

    return summarize_results(merged)


def evaluate_all_tasks(
    translation_root: Path,
    converted_root: Path,
    py_test_dir: Path,
    py_target_dir: Path,
    cpp_target_dir: Path,
    timeout_sec: int,
    threshold: float,
) -> Tuple[List[Dict[str, object]], List[Dict[str, object]]]:
    task_dirs = list_task_dirs(translation_root)
    if not task_dirs:
        raise RuntimeError(f"No supported translation tasks found under: {translation_root}")

    raw_items: List[Dict[str, object]] = []
    converted_items: List[Dict[str, object]] = []

    print(f"Found tasks: {[name for name, _ in task_dirs]}")
    for direction, raw_dir in task_dirs:
        print(f"\n[RAW] {direction}: {raw_dir}")
        raw_part = evaluate_direction(direction, raw_dir, py_test_dir, timeout_sec)
        raw_items.extend(raw_part)
        print(f"  tasks={len(raw_part)}, passed={sum(1 for x in raw_part if x['failed']==0)}")

        converted_dir = converted_root / direction
        convert_direction(direction, raw_dir, converted_dir, py_target_dir, cpp_target_dir, threshold)
        print(f"[CONVERTED] {direction}: {converted_dir}")
        converted_part = evaluate_direction(direction, converted_dir, py_test_dir, timeout_sec)
        converted_items.extend(converted_part)
        print(f"  tasks={len(converted_part)}, passed={sum(1 for x in converted_part if x['failed']==0)}")

    raw_items.sort(key=lambda x: x["task_id"])
    converted_items.sort(key=lambda x: x["task_id"])
    return raw_items, converted_items


def main() -> None:
    class_eval_root = Path(__file__).resolve().parent
    parser = argparse.ArgumentParser(description="Evaluate ClassEval-T translation (raw vs converted)")
    parser.add_argument("--translation-root", type=str, default=str(DEFAULT_TRANSLATION_ROOT))
    parser.add_argument("--output-dir", type=str, default=str(DEFAULT_OUTPUT_DIR))
    parser.add_argument("--timeout", type=int, default=20, help="Per-task timeout in seconds")
    parser.add_argument("--threshold", type=float, default=0.5, help="Signature matching threshold")
    args = parser.parse_args()

    translation_root = Path(args.translation_root).resolve()
    output_dir = Path(args.output_dir).resolve()
    converted_code_root = output_dir / "_converted_code"

    py_test_dir = (class_eval_root / "py" / "test").resolve()
    py_target_dir = (class_eval_root / "py" / "solution").resolve()
    cpp_target_dir = (class_eval_root / "cpp" / "solution").resolve()

    output_dir.mkdir(parents=True, exist_ok=True)
    converted_code_root.mkdir(parents=True, exist_ok=True)

    raw_items, converted_items = evaluate_all_tasks(
        translation_root=translation_root,
        converted_root=converted_code_root,
        py_test_dir=py_test_dir,
        py_target_dir=py_target_dir,
        cpp_target_dir=cpp_target_dir,
        timeout_sec=args.timeout,
        threshold=args.threshold,
    )

    raw_payload = summarize_results(raw_items)
    converted_payload = summarize_results(converted_items)
    union_payload = build_union_results(raw_items, converted_items)

    raw_path = output_dir / "result_raw.json"
    converted_path = output_dir / "result_converted.json"
    union_path = output_dir / "results.json"
    raw_path.write_text(json.dumps(raw_payload, ensure_ascii=False, indent=2), encoding="utf-8")
    converted_path.write_text(json.dumps(converted_payload, ensure_ascii=False, indent=2), encoding="utf-8")
    union_path.write_text(json.dumps(union_payload, ensure_ascii=False, indent=2), encoding="utf-8")

    print("\n" + "=" * 80)
    print("SUMMARY")
    print("=" * 80)
    print(f"RAW:        total={raw_payload['total']}, passed={raw_payload['passed']}, failed={raw_payload['failed']}")
    print(
        f"CONVERTED:  total={converted_payload['total']}, "
        f"passed={converted_payload['passed']}, failed={converted_payload['failed']}"
    )
    print(f"UNION:      total={union_payload['total']}, passed={union_payload['passed']}, failed={union_payload['failed']}")
    print(f"Saved: {raw_path}")
    print(f"Saved: {converted_path}")
    print(f"Saved: {union_path}")


if __name__ == "__main__":
    main()
