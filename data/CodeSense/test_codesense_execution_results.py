from __future__ import annotations

import argparse
import ast
import json
import re
from pathlib import Path
from typing import Any


def load_jsonl(path: Path):
    with path.open("r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            try:
                yield json.loads(line)
            except json.JSONDecodeError:
                continue


def to_text(value: Any) -> str:
    if isinstance(value, str):
        return value
    if value is None:
        return "null"
    if isinstance(value, bool):
        return "true" if value else "false"
    return json.dumps(value, ensure_ascii=False)


def normalize(val: str | None) -> str:
    return val.strip() if isinstance(val, str) else ""


def strip_quotes(val: str) -> str:
    if len(val) >= 2 and val[0] == val[-1] and val[0] in {"'", '"'}:
        return val[1:-1]
    return val


def canonical_literal(val: str) -> str:
    lowered = val.strip().lower()
    if lowered in {"none", "null"}:
        return "null"
    if lowered in {"true", "false"}:
        return lowered
    return val


def strip_quotes_iter(val: str) -> str:
    text = val.strip()
    while len(text) >= 2 and text[0] == text[-1] and text[0] in {"'", '"'}:
        text = text[1:-1].strip()
    return text


def decode_string_like(val: str) -> str:
    text = val.strip()
    if len(text) >= 2 and text[0] == text[-1] and text[0] in {"'", '"'}:
        try:
            parsed = ast.literal_eval(text)
            if isinstance(parsed, str):
                text = parsed
        except Exception:
            pass

    text = (
        text.replace("\\r\\n", "\n")
        .replace("\\n", "\n")
        .replace("\\t", "\t")
        .replace("\\r", "\n")
    )
    return text


def normalize_format(val: Any, language: str) -> str:
    text = normalize(to_text(val))
    text = canonical_literal(text)
    text = decode_string_like(text)
    text = strip_quotes_iter(text)

    text = text.replace('"', "").replace("'", "")
    text = "\n".join(line.strip() for line in text.splitlines())

    if language == "java":
        text = text.replace("_", " ")
        text = re.sub(r":(?=\s|$)", "", text)

    text = re.sub(r"\s+", " ", text).strip().lower()
    return text


def normalize_loose_format(val: Any, language: str) -> str:
    text = normalize_format(val, language)
    text = text.replace("/", " ").replace("\\", " ")
    text = re.sub(r"[^\w\s]+", " ", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text


def extract_expected(record: dict[str, Any]) -> Any:
    language = str(record.get("language", "")).lower()
    expected = record.get("expected_output")

    if language == "java" and isinstance(expected, list) and expected:
        first = expected[0]
        if isinstance(first, dict):
            return first.get("value")
        return first

    return expected


def is_match(raw_answer: Any, expected_output: Any, language: str) -> bool:
    raw = normalize(to_text(raw_answer))
    exp = normalize(to_text(expected_output))

    raw_candidates = {
        raw,
        strip_quotes(raw),
        canonical_literal(raw),
        canonical_literal(strip_quotes(raw)),
    }
    exp_candidates = {
        exp,
        strip_quotes(exp),
        canonical_literal(exp),
        canonical_literal(strip_quotes(exp)),
    }
    if any(r == e for r in raw_candidates for e in exp_candidates):
        return True

    if normalize_format(raw_answer, language) == normalize_format(expected_output, language):
        return True

    # More tolerant fallback for formatting-only noise such as escaped newlines,
    # underscores vs spaces, quotes, slashes, commas, and extra punctuation.
    return normalize_loose_format(raw_answer, language) == normalize_loose_format(expected_output, language)


def evaluate(input_path: Path, output_path: Path):
    results = []
    total = passed = 0

    for record in load_jsonl(input_path):
        task_id = record.get("task_id") or record.get("id")
        raw_answer_orig = record.get("raw_answer")
        expected_orig = extract_expected(record)

        language = str(record.get("language", "")).lower()
        match = is_match(raw_answer_orig, expected_orig, language=language)
        failed = 0 if match else 1

        total += 1
        if failed == 0:
            passed += 1

        results.append(
            {
                "task_id": task_id,
                "failed": failed,
                "raw_answer": raw_answer_orig,
                "expected_output": expected_orig,
            }
        )

    output = {
        "total": total,
        "passed": passed,
        "failed": total - passed,
        "results": results,
    }
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with output_path.open("w", encoding="utf-8") as f:
        json.dump(output, f, ensure_ascii=False, indent=2)

    print(f"[summary] total={total}, passed={passed}, failed={total - passed}")
    print(f"[saved] {output_path}")


def main():
    parser = argparse.ArgumentParser(
        description=(
            "Evaluate CodeSense execution JSONL by normalized string match. "
            "Java uses expected_output[0].value; Python uses expected_output directly."
        )
    )
    parser.add_argument(
        "--input",
        default="/Users/bytedance/XLLM_COT/data/derived_cot/rq3_prompting/results/execution/glm-5.1/results.jsonl",
        help="Path to generated JSONL (with language/raw_answer/expected_output).",
    )
    parser.add_argument(
        "--output",
        default="/Users/bytedance/XLLM_COT/data/derived_cot/rq3_prompting/eval/pattern_guided/execution/glm-5.1/result.jsonl",
        help="Path to save evaluation JSON.",
    )
    args = parser.parse_args()

    evaluate(Path(args.input), Path(args.output))


if __name__ == "__main__":
    main()
