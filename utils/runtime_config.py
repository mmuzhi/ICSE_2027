"""API runtime defaults loaded from environment variables."""

from __future__ import annotations

import os
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ENV_PATH = ROOT / ".env"


def load_env_file(path: Path = ENV_PATH) -> None:
    if not path.exists():
        return
    for raw in path.read_text(encoding="utf-8").splitlines():
        line = raw.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.removeprefix("export ").split("=", 1)
        key = key.strip()
        if key and key not in os.environ:
            os.environ[key] = value.strip().strip('"').strip("'")


def env_value(*names: str) -> str:
    return next((os.environ.get(name, "") for name in names if os.environ.get(name)), "")


def api_alias(alias: str | None = None) -> str:
    load_env_file()
    return (alias or env_value("DEFAULT_MODEL_ALIAS")).strip().lower()


def api_defaults(alias: str | None = None) -> dict[str, str]:
    load_env_file()
    prefix = api_alias(alias).upper()
    keys = [f"{prefix}_" if prefix else "", ""]
    return {
        "base_url": env_value(*(key + "BASE_URL" for key in keys)),
        "api_key": env_value(*(key + "API_KEY" for key in keys)),
        "model": env_value(*(key + "MODEL" for key in keys)),
    }
