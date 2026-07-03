import argparse
import json
from pathlib import Path
from typing import Any, Dict, Iterable, List


def read_jsonl(path: Path) -> List[Dict[str, Any]]:
    records: List[Dict[str, Any]] = []
    with path.open("r", encoding="utf-8") as f:
        for line_no, raw in enumerate(f, 1):
            line = raw.strip()
            if not line:
                continue
            try:
                obj = json.loads(line)
            except json.JSONDecodeError as exc:
                raise ValueError(f"Invalid JSON at {path}:{line_no}") from exc
            if not isinstance(obj, dict):
                raise ValueError(f"JSON object expected at {path}:{line_no}")
            records.append(obj)
    return records


def normalize_category(raw: Any) -> str:
    text = str(raw).strip() if raw is not None else ""
    if not text:
        return "Unknown"
    lowered = text.lower().replace("_", " ")
    if lowered in {"super easy", "easy"}:
        return "Easy"
    if lowered == "medium":
        return "Medium"
    if lowered == "hard":
        return "Hard"
    return text


def normalize_java_record(record: Dict[str, Any]) -> Dict[str, Any]:
    return {
        "language": "java",
        "code": str(record.get("code", "")),
        "input": record.get("basic_input", []),
        "output": record.get("output", []),
        "category": normalize_category(record.get("category")),
    }


def normalize_python_record(record: Dict[str, Any]) -> Dict[str, Any]:
    return {
        "language": "python",
        "code": str(record.get("code", "")),
        "input": record.get("input", ""),
        "output": record.get("output", ""),
        "category": normalize_category(record.get("category")),
    }


def add_task_ids(records: Iterable[Dict[str, Any]], start_index: int = 0) -> List[Dict[str, Any]]:
    output: List[Dict[str, Any]] = []
    next_id = start_index
    for row in records:
        new_row = dict(row)
        new_row["task_id"] = f"sample-{next_id}"
        output.append(new_row)
        next_id += 1
    return output


def write_jsonl(path: Path, records: Iterable[Dict[str, Any]]) -> int:
    count = 0
    with path.open("w", encoding="utf-8") as f:
        for row in records:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")
            count += 1
    return count


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Normalize CodeSense Java/Python datasets to a unified schema."
    )
    parser.add_argument(
        "--java-input",
        type=Path,
        default=Path("data/CodeSense/input_output_dataset_java.jsonl"),
    )
    parser.add_argument(
        "--python-input",
        type=Path,
        default=Path("data/CodeSense/input_output_dataset_python.jsonl"),
    )
    parser.add_argument(
        "--java-output",
        type=Path,
        default=Path("data/CodeSense/input_output_dataset_java_optimized.jsonl"),
    )
    parser.add_argument(
        "--python-output",
        type=Path,
        default=Path("data/CodeSense/input_output_dataset_python_optimized.jsonl"),
    )
    parser.add_argument(
        "--merged-output",
        type=Path,
        default=Path("data/CodeSense/input_output_dataset_optimized_all.jsonl"),
    )
    return parser


def main() -> None:
    parser = build_parser()
    args = parser.parse_args()

    java_raw = read_jsonl(args.java_input)
    python_raw = read_jsonl(args.python_input)

    java_normalized = [normalize_java_record(r) for r in java_raw]
    python_normalized = [normalize_python_record(r) for r in python_raw]

    java_with_ids = add_task_ids(java_normalized, start_index=0)
    python_with_ids = add_task_ids(python_normalized, start_index=0)
    merged_with_ids = add_task_ids(
        java_normalized + python_normalized,
        start_index=0,
    )

    java_count = write_jsonl(args.java_output, java_with_ids)
    python_count = write_jsonl(args.python_output, python_with_ids)
    merged_count = write_jsonl(args.merged_output, merged_with_ids)

    print(f"Java written: {java_count} -> {args.java_output}")
    print(f"Python written: {python_count} -> {args.python_output}")
    print(f"Merged written: {merged_count} -> {args.merged_output}")


if __name__ == "__main__":
    main()
