import json
import os


class CookiesUtil:
    def __init__(self, cookies_file):
        self.cookies_file = cookies_file
        self.cookies = None

    def get_cookies(self, response):
        self.cookies = response.get("cookies")
        self._save_cookies()

    def load_cookies(self):
        try:
            with open(self.cookies_file, 'r') as f:
                data = json.load(f)
            cookies_data = {}
            for key, value in data.items():
                cookies_data[str(key)] = str(value)
            return cookies_data
        except (FileNotFoundError, json.JSONDecodeError, PermissionError):
            return {}

    def _save_cookies(self):
        try:
            data = {} if self.cookies is None else self.cookies
            with open(self.cookies_file, 'w') as f:
                json.dump(data, f)
            return True
        except (FileNotFoundError, PermissionError, OSError) as e:
            return False

    def set_cookies(self, request):
        if self.cookies is None:
            cookies_str = ""
        else:
            cookies_list = [f"{key}={value}" for key, value in self.cookies.items()]
            cookies_str = "; ".join(cookies_list)
        request["cookies"] = cookies_str