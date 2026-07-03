import argparse
import json
import re
import shutil
from pathlib import Path
from typing import Any


STRICT_PATTERNS: dict[str, re.Pattern[str]] = {
    "cannot_determine": re.compile(
        r"\b(cannot|can't|unable to)\s+(determine|know)\b", re.IGNORECASE
    ),
    "ambiguous_or_incomplete": re.compile(
        r"\b(ambiguous|not clear|incomplete code context|missing (context|details|information))\b",
        re.IGNORECASE,
    ),
    "ask_for_more_info": re.compile(
        r"\b(if you can provide|please provide|need more (details|context|information)|without (knowing|more information))\b",
        re.IGNORECASE,
    ),
    "undefined_behavior": re.compile(r"\bundefined behavior\b", re.IGNORECASE),
}

AGGRESSIVE_PATTERNS: dict[str, re.Pattern[str]] = {
    "depends_on_external_context": re.compile(
        r"\bdepends on\b.{0,180}\b(system|locale|time zone|timezone|implementation|configuration|context|environment|client)\b",
        re.IGNORECASE | re.DOTALL,
    ),
    "non_deterministic_statement": re.compile(
        r"\b(exact output (cannot|can't|could not|is not) be determined|output depends on)\b",
        re.IGNORECASE,
    ),
}


def sanitize_filename(text: str) -> str:
    return re.sub(r'[\\/:*?"<>|]+', "_", text)


def read_jsonl(path: Path) -> list[dict[str, Any]]:
    records: list[dict[str, Any]] = []
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


def write_jsonl(path: Path, rows: list[dict[str, Any]]) -> None:
    with path.open("w", encoding="utf-8") as f:
        for row in rows:
            f.write(json.dumps(row, ensure_ascii=False) + "\n")


def dedupe(items: list[str]) -> list[str]:
    seen: set[str] = set()
    out: list[str] = []
    for item in items:
        if item in seen:
            continue
        seen.add(item)
        out.append(item)
    return out


def extract_ans_content(text: str) -> str | None:
    if not text:
        return None
    match = re.search(r"<ans>(.*?)</ans>", text, re.IGNORECASE | re.DOTALL)
    if not match:
        return None
    return match.group(1).strip()


def detect_invalid_reasons(row: dict[str, Any], mode: str) -> list[str]:
    reasons: list[str] = []
    answer = str(row.get("answer", "") or "")
    raw_answer_full = str(row.get("raw_answer_full", "") or "")
    text = answer
    stripped = text.strip()
    lowered = stripped.lower()

    if mode == "ans_tag":
        ans_content = extract_ans_content(raw_answer_full)
        if ans_content is None:
            reasons.append("missing_ans_tag")
            return reasons
        if ans_content == "":
            reasons.append("empty_ans_content")
            return reasons
        return reasons

    if not stripped:
        reasons.append("empty_answer")
        return reasons

    if "<think>" in lowered or "</think>" in lowered:
        reasons.append("think_tag_leak")

    for reason, pattern in STRICT_PATTERNS.items():
        if pattern.search(stripped):
            reasons.append(reason)

    if mode == "aggressive":
        for reason, pattern in AGGRESSIVE_PATTERNS.items():
            if pattern.search(stripped):
                reasons.append(reason)

    return dedupe(reasons)


def resolve_output_paths(
    results_path: Path, cleaned_path: Path | None, invalid_report_path: Path | None
) -> tuple[Path, Path]:
    default_cleaned = results_path.with_name(f"{results_path.stem}.cleaned{results_path.suffix}")
    default_report = results_path.with_name(f"{results_path.stem}.invalid{results_path.suffix}")
    return cleaned_path or default_cleaned, invalid_report_path or default_report


def classify_records(
    records: list[dict[str, Any]], mode: str
) -> tuple[list[dict[str, Any]], list[dict[str, Any]]]:
    kept: list[dict[str, Any]] = []
    invalid: list[dict[str, Any]] = []

    for row in records:
        answer = str(row.get("answer", "") or "")
        reasons = detect_invalid_reasons(row, mode=mode)
        if reasons:
            invalid.append(
                {
                    "task_id": str(row.get("task_id", "")),
                    "reasons": reasons,
                    "answer_preview": answer[:300],
                }
            )
        else:
            kept.append(row)
    return kept, invalid


def apply_txt_actions(
    invalid_rows: list[dict[str, Any]],
    output_dir: Path,
    txt_action: str,
    trash_dir: Path,
) -> tuple[int, int]:
    moved_or_deleted = 0
    missing = 0

    if txt_action == "move":
        trash_dir.mkdir(parents=True, exist_ok=True)

    for row in invalid_rows:
        task_id = str(row.get("task_id", ""))
        if not task_id:
            continue
        src = output_dir / f"{sanitize_filename(task_id)}.txt"
        if not src.exists():
            missing += 1
            continue

        if txt_action == "delete":
            src.unlink()
            moved_or_deleted += 1
        elif txt_action == "move":
            dst = trash_dir / src.name
            if dst.exists():
                stem = dst.stem
                suffix = dst.suffix
                index = 1
                while True:
                    candidate = trash_dir / f"{stem}_{index}{suffix}"
                    if not candidate.exists():
                        dst = candidate
                        break
                    index += 1
            shutil.move(str(src), str(dst))
            moved_or_deleted += 1

    return moved_or_deleted, missing


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Filter invalid Execution_COT samples with no valid final answer and optionally "
            "clean corresponding txt files."
        )
    )
    parser.add_argument(
        "--results",
        type=Path,
        required=True,
        help="Path to results.jsonl (e.g., data/CodeSense/Execution_COT/qwen/results.jsonl).",
    )
    parser.add_argument(
        "--mode",
        choices=["strict", "aggressive", "ans_tag"],
        default="strict",
        help=(
            "strict: clear non-answers; "
            "aggressive: also remove depends-on external context; "
            "ans_tag: keep only samples with non-empty <ans>...</ans> in raw_answer_full."
        ),
    )
    parser.add_argument(
        "--cleaned-results",
        type=Path,
        default=None,
        help="Output path for cleaned JSONL. Default: <results>.cleaned.jsonl",
    )
    parser.add_argument(
        "--invalid-report",
        type=Path,
        default=None,
        help="Output path for invalid report JSONL. Default: <results>.invalid.jsonl",
    )
    parser.add_argument(
        "--preview",
        type=int,
        default=20,
        help="How many invalid task_ids to preview in terminal.",
    )
    parser.add_argument(
        "--apply",
        action="store_true",
        help="Apply changes in-place to --results (with .bak backup).",
    )
    parser.add_argument(
        "--output-dir",
        type=Path,
        default=None,
        help="Directory containing sample-xxx.txt files for optional cleanup.",
    )
    parser.add_argument(
        "--txt-action",
        choices=["none", "move", "delete"],
        default="none",
        help="How to handle invalid txt files when --apply is used.",
    )
    parser.add_argument(
        "--trash-dir",
        type=Path,
        default=None,
        help="Used when --txt-action move. Default: <output-dir>/_invalid_samples",
    )
    return parser


def main() -> None:
    parser = build_parser()
    args = parser.parse_args()

    if not args.results.exists():
        raise FileNotFoundError(f"Results file not found: {args.results}")

    if args.txt_action != "none":
        if not args.output_dir:
            raise ValueError("--output-dir is required when --txt-action is not none")
        if not args.apply:
            raise ValueError("--txt-action requires --apply")

    records = read_jsonl(args.results)
    kept, invalid = classify_records(records, mode=args.mode)

    cleaned_path, invalid_report_path = resolve_output_paths(
        args.results, args.cleaned_results, args.invalid_report
    )
    cleaned_path.parent.mkdir(parents=True, exist_ok=True)
    invalid_report_path.parent.mkdir(parents=True, exist_ok=True)
    write_jsonl(cleaned_path, kept)
    write_jsonl(invalid_report_path, invalid)

    print(f"Results total: {len(records)}")
    print(f"Invalid found: {len(invalid)}")
    print(f"Kept records : {len(kept)}")
    print(f"Cleaned JSONL: {cleaned_path}")
    print(f"Invalid report: {invalid_report_path}")
    preview_ids = [str(row.get("task_id", "")) for row in invalid[: args.preview]]
    if preview_ids:
        print(f"Preview invalid task_ids ({len(preview_ids)}): {preview_ids}")

    if not args.apply:
        print("Dry run only. Use --apply to replace original results.")
        return

    backup_path = args.results.with_suffix(args.results.suffix + ".bak")
    shutil.copy2(args.results, backup_path)
    shutil.copy2(cleaned_path, args.results)
    print(f"Backup created: {backup_path}")
    print(f"Replaced in-place: {args.results}")

    if args.txt_action != "none":
        output_dir = args.output_dir
        if output_dir is None:
            raise ValueError("Internal error: output_dir is None")
        if not output_dir.exists():
            raise FileNotFoundError(f"Output dir not found: {output_dir}")
        trash_dir = args.trash_dir or (output_dir / "_invalid_samples")
        handled, missing = apply_txt_actions(invalid, output_dir, args.txt_action, trash_dir)
        print(f"TXT action={args.txt_action}: handled={handled}, missing={missing}")
        if args.txt_action == "move":
            print(f"Moved TXT dir: {trash_dir}")


if __name__ == "__main__":
    main()
