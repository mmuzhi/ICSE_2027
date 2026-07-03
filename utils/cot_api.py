"""CoT API helpers."""

from __future__ import annotations

import time

from .cot_io import safe_print


EXTRA_BODY = {"chat_template_kwargs": {"enable_thinking": True, "clear_thinking": False}}


def _call_api(
    prompt: str,
    api_key: str,
    base_url: str,
    model_name: str,
    max_tokens: int = 8192,
    temperature: float = 0.6,
    top_p: float = 0.95,
    max_retries: int = 2,
    task_id: str = "unknown",
    request_timeout: float | None = 180.0,
    before_request=None,
    stream: bool = True,
) -> tuple[str, str, bool, str | None]:
    from openai import OpenAI

    client = OpenAI(base_url=base_url, api_key=api_key)

    for attempt in range(max_retries):
        try:
            if before_request:
                before_request()

            kwargs = {
                "model": model_name,
                "messages": [{"role": "user", "content": prompt}],
                "stream": stream,
                "max_tokens": max_tokens,
                "temperature": temperature,
                "extra_body": EXTRA_BODY,
                "top_p": top_p,
            }
            if request_timeout is not None:
                kwargs["timeout"] = request_timeout
            response = client.chat.completions.create(**kwargs)
            if not stream:
                choice = response.choices[0]
                return getattr(choice.message, "reasoning_content", "") or "", choice.message.content or "", True, None

            reasoning_parts: list[str] = []
            answer_parts: list[str] = []
            for chunk in response:
                if not chunk.choices:
                    continue
                delta = chunk.choices[0].delta
                if reasoning_content := getattr(delta, "reasoning_content", None):
                    reasoning_parts.append(reasoning_content)
                if content := getattr(delta, "content", None):
                    answer_parts.append(content)
            return "".join(reasoning_parts), "".join(answer_parts), True, None
        except Exception as ex:
            error_msg = f"Request exception: {ex}"
            safe_print(f"[{task_id}] Error (attempt {attempt + 1}/{max_retries}): {error_msg}")
            if attempt < max_retries - 1:
                time.sleep(2 ** attempt)
            else:
                return "", "", False, error_msg

    return "", "", False, "Max retries exceeded"


def call_api_stream(*args, **kwargs) -> tuple[str, str, bool, str | None]:
    return _call_api(*args, **kwargs, stream=True)


def call_api(*args, **kwargs) -> tuple[str, str, bool, str | None]:
    return _call_api(*args, **kwargs, stream=False)
