import json
import sys

class CookiesUtil:
    def __init__(self, cookies_file: str):
        self.cookies_file = cookies_file
        self.cookies = {}

    def get_cookies(self, response: dict):
        if "cookies" in response:
            # response["cookies"] is expected to be a dict mapping strings to strings
            self.cookies = response["cookies"]
        self._save_cookies()

    def load_cookies(self) -> dict:
        data = {}
        try:
            with open(self.cookies_file, 'r') as f:
                data = json.load(f)
        except FileNotFoundError:
            # file not present -> return empty dict (matches C++ behavior where file.open fails)
            pass
        except json.JSONDecodeError as e:
            print(f"Error reading JSON file: {e}", file=sys.stderr)
        except Exception as e:
            print(f"Error reading JSON file: {e}", file=sys.stderr)
        return data

    def _save_cookies(self) -> bool:
        try:
            with open(self.cookies_file, 'w') as f:
                json.dump(self.cookies, f, indent=4)
            return True
        except Exception as e:
            print(f"Error writing JSON file: {e}", file=sys.stderr)
            return False

    def set_cookies(self, request: dict):
        parts = []
        for key, value in self.cookies.items():
            parts.append(f"{key}={value}")
        request["cookies"] = "; ".join(parts)