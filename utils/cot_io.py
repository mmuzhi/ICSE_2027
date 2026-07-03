"""Thread-safe CoT JSONL helpers."""

import json
import os
import tempfile
import threading
from pathlib import Path


print_lock = threading.Lock()
write_lock = threading.Lock()


def safe_print(*args, **kwargs):
    with print_lock:
        print(*args, **kwargs)


def _load_task_records(path: Path, warning: str) -> dict[str, dict]:
    if not path.exists():
        return {}
    records: dict[str, dict] = {}
    try:
        with path.open("r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                try:
                    data = json.loads(line)
                    tid = data.get("task_id")
                    if tid:
                        records[str(tid)] = data
                except json.JSONDecodeError:
                    continue
    except Exception as e:
        safe_print(f"{warning}: {e}")
    return records


def _write_task_records(path: Path, records: dict[str, dict]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp_fd, temp_path = tempfile.mkstemp(suffix=".jsonl.tmp", dir=path.parent, prefix=path.stem + "_")
    temp_file = Path(temp_path)
    try:
        with os.fdopen(temp_fd, "w", encoding="utf-8") as f:
            for data in records.values():
                f.write(json.dumps(data, ensure_ascii=False) + "\n")
        temp_file.replace(path)
    except Exception:
        temp_file.unlink(missing_ok=True)
        raise


def load_existing_task_ids(save_path: str) -> set[str]:
    return set(_load_task_records(Path(save_path), "Warning: failed to load existing task_ids"))


def append_result_to_file(result: dict, save_path: str) -> bool:
    try:
        path = Path(save_path)
        path.parent.mkdir(parents=True, exist_ok=True)
        with write_lock:
            with path.open("a", encoding="utf-8") as f:
                f.write(json.dumps(result, ensure_ascii=False) + "\n")
        return True
    except Exception as e:
        safe_print(f"Error appending result to file: {e}")
        return False


def save_or_update_result(result: dict, save_path: str) -> bool:
    task_id = result.get("task_id")
    if not task_id:
        safe_print("Error: result has no task_id")
        return False
    
    path = Path(save_path)
    try:
        with write_lock:
            existing = _load_task_records(path, "Warning: failed to load existing results")
            existing[str(task_id)] = result
            _write_task_records(path, existing)
        return True
    except Exception as e:
        safe_print(f"Error saving result: {e}")
        return False


def load_existing_results(save_path: str) -> dict:
    return _load_task_records(Path(save_path), "Warning: failed to load existing results")


def consolidate_jsonl(file_path: str) -> int:
    path = Path(file_path)
    if not path.exists():
        return 0
    
    tasks = _load_task_records(path, "Warning: failed to read file for consolidation")
    if not tasks:
        return 0
    
    try:
        _write_task_records(path, tasks)
        safe_print(f"Consolidated {file_path}: {len(tasks)} unique tasks")
        return len(tasks)
    except Exception as e:
        safe_print(f"Error during consolidation: {e}")
        return 0
