import os
import json
import time
import re
import requests
from pathlib import Path

CSRF_TOKEN = "HHm9r8YwudRIIsPlikuHTIC47aad3nNo"
LEETCODE_SESSION = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJuZXh0X2FmdGVyX29hdXRoIjoiL3Byb2JsZW1zZXQvIiwiX2F1dGhfdXNlcl9pZCI6IjI3MjAzMTEiLCJfYXV0aF91c2VyX2JhY2tlbmQiOiJkamFuZ28uY29udHJpYi5hdXRoLmJhY2tlbmRzLk1vZGVsQmFja2VuZCIsIl9hdXRoX3VzZXJfaGFzaCI6ImI2MDg3NDFhMWVmMjQ1Yzg1NmNlZDU3NjkzNjRmNzcxYmYxOTk0YTU0MTUwZmY0MWQxM2RiMWIwNzVkZjMyODQiLCJpZCI6MjcyMDMxMSwiZW1haWwiOiIxNDU3NzY2NTIzQHFxLmNvbSIsInVzZXJuYW1lIjoiZW11LXpoaS1lIiwidXNlcl9zbHVnIjoiZW11LXpoaS1lIiwiYXZhdGFyIjoiaHR0cHM6Ly9hc3NldHMubGVldGNvZGUuY24vYWxpeXVuLWxjLXVwbG9hZC91c2Vycy9lbXUtemhpLWUvYXZhdGFyXzE2NjkwMTA2MzAucG5nIiwicGhvbmVfdmVyaWZpZWQiOnRydWUsImlwIjoiMjcuMTE1LjEyMy4yNTEiLCJfdGltZXN0YW1wIjoxNzczMTAzNzExLjY1OTcyNjYsImV4cGlyZWRfdGltZV8iOjE3NzU2NzQ4MDAsInZlcnNpb25fa2V5XyI6MSwiZGV2aWNlX2lkIjoiM2FiZDI0MzE3MTRkODc5NzE3N2EwMDU1MTNjMWQ1YWQifQ.JaKWPAGp-9WiFpg8ZtvcyomC4JWuyaXb0gh_LOXULOA"
COOLDOWN = 10

SAMPLES_FILE = Path(__file__).parent / "python_samples.json"
CODE_OUTPUT_DIR = Path(__file__).parent / "Debug_COT" / "r1" /"code_output"
RESULT_FILE = Path(__file__).parent.parent.parent /"RQ2"/"test"/"debug"/"r1"/"results.json"


def build_result_record(task_id, passed, status, slug=None):
    record = {
        "task_id": task_id,
        "total": 1,
        "passed": 1 if passed else 0,
        "failed": 0 if passed else 1,
        "status": status,
    }
    if slug:
        record["slug"] = slug
    return record

class LeetCodeCN:
    BASE_URL = "https://leetcode.cn"
    GRAPHQL_URL = f"{BASE_URL}/graphql/"
    
    def __init__(self, csrf_token, session_token, cooldown=10):
        self.cooldown = cooldown
        self.last_request_time = 0
        self.last_error = None
        self.session = requests.Session()
        self.session.cookies.set("csrftoken", csrf_token, domain="leetcode.cn")
        self.session.cookies.set("LEETCODE_SESSION", session_token, domain="leetcode.cn")
        self.session.headers.update({
            "Content-Type": "application/json",
            "x-csrftoken": csrf_token,
            "Referer": "https://leetcode.cn/",
            "Origin": "https://leetcode.cn",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36"
        })
    
    def _wait_cooldown(self):
        elapsed = time.time() - self.last_request_time
        if elapsed < self.cooldown:
            time.sleep(self.cooldown - elapsed)
        self.last_request_time = time.time()

    def _strip_manual_numeric_suffix(self, slug):
        return re.sub(r"-\d+$", "", slug)

    def _response_preview(self, response, limit=240):
        text = response.text or ""
        text = re.sub(r"\s+", " ", text).strip()
        if len(text) > limit:
            text = text[:limit] + "..."
        return text or "<empty body>"

    def _format_response_error(self, stage, response, error):
        content_type = response.headers.get("Content-Type", "<missing>")
        preview = self._response_preview(response)
        return (
            f"{stage} invalid json: {error}; "
            f"http_status={response.status_code}; "
            f"content_type={content_type}; "
            f"body={preview}"
        )

    def _parse_json_response(self, response, stage):
        try:
            return response.json(), None
        except ValueError as error:
            return None, self._format_response_error(stage, response, error)

    def _request_exception_message(self, stage, error):
        return f"{stage} request failed: {type(error).__name__}: {error}"

    def resolve_slug_and_question_id(self, slug):
        question_id = self.get_question_id(slug)
        if question_id:
            return slug, question_id

        normalized_slug = self._strip_manual_numeric_suffix(slug)
        if normalized_slug == slug:
            return slug, None

        question_id = self.get_question_id(normalized_slug)
        if question_id:
            return normalized_slug, question_id
        return slug, None
    
    def get_question_id(self, slug):
        query = """
        query questionData($titleSlug: String!) {
            question(titleSlug: $titleSlug) { questionId }
        }
        """
        try:
            resp = self.session.post(
                self.GRAPHQL_URL,
                json={"query": query, "variables": {"titleSlug": slug}},
                timeout=30,
            )
            data, error = self._parse_json_response(resp, f"graphql slug={slug}")
            if error:
                self.last_error = error
                return None
            if not isinstance(data, dict):
                self.last_error = f"graphql slug={slug} returned non-dict payload: {type(data).__name__}"
                return None

            question = (data.get("data") or {}).get("question")
            if question is None:
                self.last_error = f"graphql slug={slug} returned question=null; payload={data}"
                return None

            if not isinstance(question, dict):
                self.last_error = f"graphql slug={slug} returned unexpected question payload: {question}"
                return None

            return question.get("questionId")
        except requests.RequestException as error:
            self.last_error = self._request_exception_message(f"graphql slug={slug}", error)
            return None
    
    def submit_code(self, slug, code):
        self.last_error = None
        self._wait_cooldown()
        resolved_slug, question_id = self.resolve_slug_and_question_id(slug)
        if not question_id:
            return False, self.last_error or "cannot get question_id"
        
        submit_url = f"{self.BASE_URL}/problems/{resolved_slug}/submit/"
        try:
            resp = self.session.post(
                submit_url,
                json={
                    "lang": "python3",
                    "question_id": question_id,
                    "typed_code": code
                },
                timeout=30,
            )
            result, error = self._parse_json_response(resp, f"submit slug={resolved_slug}")
            if error:
                return False, error
            if "submission_id" not in result:
                return False, str(result)
            return self._wait_for_result(result["submission_id"])
        except requests.RequestException as error:
            return False, self._request_exception_message(f"submit slug={resolved_slug}", error)
    
    def _wait_for_result(self, submission_id, max_wait=60):
        check_url = f"{self.BASE_URL}/submissions/detail/{submission_id}/check/"
        start = time.time()
        while time.time() - start < max_wait:
            try:
                resp = self.session.get(check_url, timeout=30)
                result, error = self._parse_json_response(resp, f"check submission_id={submission_id}")
                if error:
                    return False, error
                state = result.get("state")
                if state == "SUCCESS":
                    status_msg = result.get("status_msg", "Unknown")
                    return status_msg == "Accepted", status_msg
                elif state in ["PENDING", "STARTED"]:
                    time.sleep(2)
                else:
                    return False, f"state: {state}"
            except requests.RequestException as error:
                return False, self._request_exception_message(f"check submission_id={submission_id}", error)
        return False, "timeout"


def load_sample_slug_map():
    with open(SAMPLES_FILE, 'r', encoding='utf-8') as f:
        samples = json.load(f)
    return {
        sample["sample_id"]: sample["slug"]
        for sample in samples
        if sample.get("sample_id") and sample.get("slug")
    }


def load_existing_results():
    if RESULT_FILE.exists():
        with open(RESULT_FILE, 'r', encoding='utf-8') as f:
            data = json.load(f)
        results = {r["task_id"]: r for r in data.get("results", [])}
        return results
    return {}


def save_results(results):
    output = {"results": list(results.values())}
    RESULT_FILE.parent.mkdir(parents=True, exist_ok=True)
    with open(RESULT_FILE, 'w', encoding='utf-8') as f:
        json.dump(output, f, ensure_ascii=False, indent=2)


def main():
    code_files = sorted(CODE_OUTPUT_DIR.glob("*.py"))
    leetcode = LeetCodeCN(CSRF_TOKEN, LEETCODE_SESSION, COOLDOWN)
    sample_slug_map = load_sample_slug_map()
    
    results = load_existing_results()
    print(f"Already tested {len(results)} tasks, resuming...")
    
    count = 0
    for i, filepath in enumerate(code_files):
        filename = filepath.name
        task_id = filename.replace('.py', '')
        leetcode_slug = sample_slug_map.get(task_id)
        
        if task_id in results:
            continue
        if not leetcode_slug:
            status = "slug not found in python_samples.json"
            print(f"[{i+1}/{len(code_files)}] {task_id}: failed ({status})")
            results[task_id] = build_result_record(task_id, False, status)
            save_results(results)
            continue
        
        with open(filepath, 'r', encoding='utf-8') as f:
            code = f.read()
        
        passed, status = leetcode.submit_code(leetcode_slug, code)
        print(f"[{i+1}/{len(code_files)}] {task_id}: {'passed' if passed else 'failed'} ({status})")
        results[task_id] = build_result_record(task_id, passed, status, leetcode_slug)
        save_results(results)
        
        count += 1
        if count % 5 == 0:
            print("  [saved]")
    
    save_results(results)
    total_passed = sum(r["passed"] for r in results.values())
    print(f"\nDone. Total: {len(results)}, Passed: {total_passed}, Failed: {len(results) - total_passed}")


if __name__ == "__main__":
    main()
