import argparse
import json
from pathlib import Path
from typing import Dict, List, Set, Tuple

PROJECT_ROOT = Path("/Users/bytedance/XLLM_COT")
DEFAULT_RESULTS_JSONL = PROJECT_ROOT / "data" / "DebugBench" / "Debug_COT" / "glm5.1" / "results.jsonl"


def is_empty_raw_answer(value) -> bool:
    if value is None:
        return True
    if isinstance(value, str):
        return value.strip() == ""
    return False


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


def parse_jsonl(results_path: Path) -> Tuple[List[Dict], List[Tuple[int, str]]]:
    records: List[Dict] = []
    parse_errors: List[Tuple[int, str]] = []

    with results_path.open("r", encoding="utf-8") as file:
        for line_num, line in enumerate(file, 1):
            line = line.strip()
            if not line:
                continue
            try:
                item = json.loads(line)
            except json.JSONDecodeError as error:
                parse_errors.append((line_num, str(error)))
                continue

            task_id = str(item.get("task_id", "")).strip()
            records.append(
                {
                    "line_num": line_num,
                    "task_id": task_id,
                    "empty_raw_answer": is_empty_raw_answer(item.get("raw_answer")),
                    "record": item,
                }
            )
    return records, parse_errors


def clean_results_and_txt(
    results_path: Path,
    txt_dir: Path,
    remove_task_ids: Set[str],
    output_path: Path,
    inplace: bool,
    execute: bool,
) -> None:
    records, parse_errors = parse_jsonl(results_path)

    removed_records = [record for record in records if record["task_id"] in remove_task_ids]
    kept_records = [record for record in records if record["task_id"] not in remove_task_ids]
    removed_task_ids = sorted({record["task_id"] for record in removed_records if record["task_id"]})

    print("=" * 72)
    print("Debug_COT 清理预览")
    print("=" * 72)
    print(f"results 文件: {results_path}")
    print(f"txt 目录:      {txt_dir}")
    print(f"模式:          {'执行模式' if execute else '预览模式（不落盘）'}")
    print("-" * 72)
    print(f"总记录数:      {len(records)}")
    print(f"待删除记录数:  {len(removed_records)}")
    print(f"保留记录数:    {len(kept_records)}")
    print(f"待删 task_id 数:{len(removed_task_ids)}")
    if parse_errors:
        print(f"JSON 解析失败: {len(parse_errors)} 行（保持不变）")
    print("=" * 72)

    if removed_task_ids:
        preview = ", ".join(removed_task_ids[:15])
        suffix = "" if len(removed_task_ids) <= 15 else f" ... (+{len(removed_task_ids) - 15})"
        print(f"待删除 task_id（前15个）: {preview}{suffix}")
    else:
        print("没有匹配到要删除的 task_id。")

    txt_deleted: List[str] = []
    txt_missing: List[str] = []
    for task_id in removed_task_ids:
        txt_file = txt_dir / f"{task_id}.txt"
        if txt_file.exists():
            if execute:
                txt_file.unlink()
            txt_deleted.append(str(txt_file))
        else:
            txt_missing.append(str(txt_file))

    if not execute:
        print("\n[预览] 不会修改任何文件。加 `--execute` 才会实际执行。")
        print(f"[预览] 将删除 txt: {len(txt_deleted)}")
        print(f"[预览] txt 不存在: {len(txt_missing)}")
        return

    if inplace:
        backup_path = Path(f"{results_path}.bak")
        results_path.rename(backup_path)
        write_path = results_path
        print(f"\n已备份原文件: {backup_path}")
    else:
        write_path = output_path

    with write_path.open("w", encoding="utf-8") as file:
        for item in kept_records:
            file.write(json.dumps(item["record"], ensure_ascii=False) + "\n")

    print(f"已写入清理后的 results: {write_path}")
    print(f"已删除 txt 文件: {len(txt_deleted)}")
    print(f"未找到 txt 文件: {len(txt_missing)}")


def build_remove_task_ids(
    records: List[Dict],
    include_empty_raw_answer: bool,
    manual_task_ids: Set[str],
) -> Set[str]:
    task_ids = set(manual_task_ids)
    if include_empty_raw_answer:
        for record in records:
            if record["task_id"] and record["empty_raw_answer"]:
                task_ids.add(record["task_id"])
    return task_ids


def main() -> None:
    parser = argparse.ArgumentParser(
        description="按 task_id 清理 Debug_COT 的 results.jsonl，并删除对应 txt。"
    )
    parser.add_argument(
        "results_jsonl",
        type=str,
        nargs="?",
        default=str(DEFAULT_RESULTS_JSONL),
        help="results.jsonl 路径，例如 data/DebugBench/Debug_COT/r1/results.jsonl",
    )
    parser.add_argument(
        "--txt-dir",
        type=str,
        default=None,
        help="txt_output 目录，默认是 results.jsonl 同级的 txt_output",
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
        "--no-empty-raw-answer",
        action="store_true",
        help="不自动删除 raw_answer 为空的记录，仅按手动 task_id 删除",
    )
    parser.add_argument(
        "--output",
        type=str,
        default=None,
        help="输出结果文件（默认 <results>_cleaned.jsonl）",
    )
    parser.add_argument(
        "--inplace",
        action="store_true",
        help="覆盖原 results.jsonl（会先备份为 .bak）",
    )
    parser.add_argument(
        "--execute",
        action="store_true",
        help="实际执行删除和写入（默认仅预览）",
    )
    args = parser.parse_args()

    results_path = Path(args.results_jsonl)
    if not results_path.exists():
        raise FileNotFoundError(f"results 文件不存在: {results_path}")

    txt_dir = Path(args.txt_dir) if args.txt_dir else results_path.parent / "txt_output"
    output_path = Path(args.output) if args.output else results_path.with_name(f"{results_path.stem}_cleaned.jsonl")
    if args.inplace:
        output_path = results_path

    records, parse_errors = parse_jsonl(results_path)
    if parse_errors:
        print(f"警告: 存在 {len(parse_errors)} 行 JSON 解析失败，这些行将被保留不改动。")

    manual_task_ids: Set[str] = set(args.task_id)
    if args.task_id_file:
        manual_task_ids.update(load_task_ids_from_file(Path(args.task_id_file)))

    remove_task_ids = build_remove_task_ids(
        records=records,
        include_empty_raw_answer=not args.no_empty_raw_answer,
        manual_task_ids=manual_task_ids,
    )

    if not remove_task_ids:
        print("没有找到可删除 task_id（既没有空 raw_answer，也没有手动 task_id）。")
        return

    clean_results_and_txt(
        results_path=results_path,
        txt_dir=txt_dir,
        remove_task_ids=remove_task_ids,
        output_path=output_path,
        inplace=args.inplace,
        execute=args.execute,
    )


if __name__ == "__main__":
    main()
