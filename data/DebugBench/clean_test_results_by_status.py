import argparse
import json
from collections import Counter
from pathlib import Path
from typing import Dict, Iterable, List, Set, Tuple

PROJECT_ROOT = Path("/mnt/sda/yz/projects/XLLM_COT")
DEFAULT_TEST_RESULTS_JSON = PROJECT_ROOT / "RQ2" / "test" / "debug" / "qwen" / "results.json"
COMMON_ENV_ERROR_PATTERNS = (
    "Expecting value: line 1 column 1 (char 0)",
)


def load_task_ids_from_file(task_id_file: Path) -> Set[str]:
    task_ids: Set[str] = set()
    if not task_id_file.exists():
        raise FileNotFoundError(f"task_id 文件不存在: {task_id_file}")

    with task_id_file.open("r", encoding="utf-8") as file:
        for line in file:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            task_ids.add(line)
    return task_ids


def contains_any_pattern(text: str, patterns: Iterable[str]) -> bool:
    return any(pattern in text for pattern in patterns)


def load_test_results(test_results_path: Path) -> Dict:
    if not test_results_path.exists():
        raise FileNotFoundError(f"测试结果文件不存在: {test_results_path}")
    with test_results_path.open("r", encoding="utf-8") as file:
        return json.load(file)


def select_task_ids_by_status(
    results: List[Dict],
    status_patterns: List[str],
    failed_only: bool,
) -> Tuple[Set[str], Counter]:
    matched_task_ids: Set[str] = set()
    matched_statuses: Counter = Counter()
    for item in results:
        task_id = str(item.get("task_id", "")).strip()
        status = str(item.get("status", "")).strip()
        failed = int(item.get("failed", 0) or 0)
        if not task_id or not status:
            continue
        if failed_only and failed == 0:
            continue
        if contains_any_pattern(status, status_patterns):
            matched_task_ids.add(task_id)
            matched_statuses[status] += 1
    return matched_task_ids, matched_statuses


def build_remove_task_ids(
    results: List[Dict],
    manual_task_ids: Set[str],
    status_patterns: List[str],
    failed_only: bool,
) -> Tuple[Set[str], Counter]:
    remove_task_ids = set(manual_task_ids)
    matched_statuses: Counter = Counter()
    if status_patterns:
        matched_task_ids, matched_statuses = select_task_ids_by_status(
            results=results,
            status_patterns=status_patterns,
            failed_only=failed_only,
        )
        remove_task_ids.update(matched_task_ids)
    return remove_task_ids, matched_statuses


def preview_cleanup(results: List[Dict], remove_task_ids: Set[str], execute: bool, test_results_path: Path) -> None:
    kept_results = [item for item in results if str(item.get("task_id", "")).strip() not in remove_task_ids]
    removed_results = [item for item in results if str(item.get("task_id", "")).strip() in remove_task_ids]
    removed_task_ids = sorted({str(item.get("task_id", "")).strip() for item in removed_results if item.get("task_id")})

    print("=" * 72)
    print("测试结果清理预览")
    print("=" * 72)
    print(f"测试结果文件:  {test_results_path}")
    print(f"模式:          {'执行模式' if execute else '预览模式（不落盘）'}")
    print("-" * 72)
    print(f"总记录数:      {len(results)}")
    print(f"待删除记录数:  {len(removed_results)}")
    print(f"保留记录数:    {len(kept_results)}")
    print(f"待删 task_id 数:{len(removed_task_ids)}")
    print("=" * 72)

    if removed_task_ids:
        preview = ", ".join(removed_task_ids[:15])
        suffix = "" if len(removed_task_ids) <= 15 else f" ... (+{len(removed_task_ids) - 15})"
        print(f"待删除 task_id（前15个）: {preview}{suffix}")
    else:
        print("没有匹配到要删除的 task_id。")


def write_task_ids(task_id_output: Path, task_ids: Set[str]) -> None:
    task_id_output.parent.mkdir(parents=True, exist_ok=True)
    with task_id_output.open("w", encoding="utf-8") as file:
        for task_id in sorted(task_ids):
            file.write(task_id + "\n")
    print(f"已导出 task_id 列表: {task_id_output}")


def clean_test_results(
    test_results_path: Path,
    output_path: Path,
    remove_task_ids: Set[str],
    inplace: bool,
    execute: bool,
) -> None:
    data = load_test_results(test_results_path)
    results = data.get("results", [])
    kept_results = [item for item in results if str(item.get("task_id", "")).strip() not in remove_task_ids]

    if not execute:
        print("\n[预览] 不会修改任何文件。加 `--execute` 才会实际执行。")
        return

    if inplace:
        backup_path = Path(f"{test_results_path}.bak")
        test_results_path.rename(backup_path)
        write_path = test_results_path
        print(f"\n已备份原文件: {backup_path}")
    else:
        write_path = output_path

    data["results"] = kept_results
    write_path.parent.mkdir(parents=True, exist_ok=True)
    with write_path.open("w", encoding="utf-8") as file:
        json.dump(data, file, ensure_ascii=False, indent=2)

    print(f"已写入清理后的测试结果: {write_path}")


def main() -> None:
    parser = argparse.ArgumentParser(description="按失败原因或 task_id 清理测试结果 results.json。")
    parser.add_argument(
        "test_results_json",
        type=str,
        nargs="?",
        default=str(DEFAULT_TEST_RESULTS_JSON),
        help="测试结果 JSON 路径，例如 RQ2/test/debug/r1/results.json",
    )
    parser.add_argument(
        "--task-id",
        action="append",
        default=[],
        help="手动指定要删除的 task_id（可重复传多个）",
    )
    parser.add_argument(
        "--task-id-file",
        type=str,
        default=None,
        help="task_id 文本文件（每行一个）",
    )
    parser.add_argument(
        "--status-contains",
        action="append",
        default=[],
        help="按测试结果里的 status 子串匹配删除 task_id（可重复传多个）",
    )
    parser.add_argument(
        "--common-env-errors",
        action="store_true",
        help="自动匹配常见环境错误（当前包含空响应 JSON 解析失败）",
    )
    parser.add_argument(
        "--include-passed",
        action="store_true",
        help="默认只匹配 failed > 0 的记录；开启后连 passed 记录也参与 status 匹配",
    )
    parser.add_argument(
        "--save-task-id-file",
        type=str,
        default=None,
        help="将命中的 task_id 额外导出到文本文件，便于传给别的脚本",
    )
    parser.add_argument(
        "--output",
        type=str,
        default=None,
        help="输出结果文件（默认 <results>_cleaned.json）",
    )
    parser.add_argument(
        "--inplace",
        action="store_true",
        help="覆盖原 results.json（会先备份为 .bak）",
    )
    parser.add_argument(
        "--execute",
        action="store_true",
        help="实际执行写入（默认仅预览）",
    )
    args = parser.parse_args()

    test_results_path = Path(args.test_results_json)
    data = load_test_results(test_results_path)
    results = data.get("results", [])

    manual_task_ids: Set[str] = set(args.task_id)
    if args.task_id_file:
        manual_task_ids.update(load_task_ids_from_file(Path(args.task_id_file)))

    status_patterns = list(args.status_contains)
    if args.common_env_errors:
        status_patterns.extend(COMMON_ENV_ERROR_PATTERNS)

    remove_task_ids, matched_statuses = build_remove_task_ids(
        results=results,
        manual_task_ids=manual_task_ids,
        status_patterns=status_patterns,
        failed_only=not args.include_passed,
    )

    if status_patterns:
        print(f"根据测试 status 匹配到 task_id: {len(remove_task_ids - manual_task_ids)}")
        if matched_statuses:
            print("匹配到的失败原因：")
            for status, count in matched_statuses.most_common(10):
                print(f"  - {status}: {count}")

    if not remove_task_ids:
        print("没有找到可删除 task_id（既没有手动 task_id，也没有命中的测试失败原因）。")
        return

    if args.save_task_id_file:
        write_task_ids(Path(args.save_task_id_file), remove_task_ids)

    preview_cleanup(
        results=results,
        remove_task_ids=remove_task_ids,
        execute=args.execute,
        test_results_path=test_results_path,
    )

    output_path = Path(args.output) if args.output else test_results_path.with_name(f"{test_results_path.stem}_cleaned.json")
    if args.inplace:
        output_path = test_results_path

    clean_test_results(
        test_results_path=test_results_path,
        output_path=output_path,
        remove_task_ids=remove_task_ids,
        inplace=args.inplace,
        execute=args.execute,
    )


if __name__ == "__main__":
    main()
