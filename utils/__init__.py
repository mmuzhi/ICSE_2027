"""Shared CoT helpers."""

from .cot_io import (
    print_lock,
    write_lock,
    safe_print,
    load_existing_task_ids,
    append_result_to_file,
    save_or_update_result,
    load_existing_results,
    consolidate_jsonl,
)
from .runtime_config import api_alias, api_defaults


def call_api_stream(*args, **kwargs):
    from .cot_api import call_api_stream as _call_api_stream

    return _call_api_stream(*args, **kwargs)

__all__ = [
    "print_lock",
    "write_lock", 
    "safe_print",
    "load_existing_task_ids",
    "append_result_to_file",
    "save_or_update_result",
    "load_existing_results",
    "consolidate_jsonl",
    "api_alias",
    "api_defaults",
    "call_api_stream",
]
