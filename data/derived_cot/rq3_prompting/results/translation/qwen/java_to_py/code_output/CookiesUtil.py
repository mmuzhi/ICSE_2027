import json
from pathlib import Path

class CookiesUtil:
    def __init__(self, cookies_file):
        self.cookies_file = cookies_file
        self.cookies = None

    def get_cookies(self, response):
        if "cookies" in response:
            cookies_value = response["cookies"]
            if cookies_value is None:
                self.cookies = {}
            else:
                self.cookies = cookies_value
        else:
            self.cookies = {}
        self._save_cookies()

    def load_cookies(self):
        try:
            with open(self.cookies_file, 'r') as file:
                data = json.load(file)
                return data
        except (FileNotFoundError, json.JSONDecodeError):
            return {}

    def _save_cookies(self):
        try:
            with open(self.cookies_file, 'w') as file:
                if self.cookies is None:
                    file.write("{}")
                else:
                    json.dump(self.cookies, file, indent=None)
            return True
        except Exception as e:
            print(f"Error saving cookies: {e}")
            return False

    def set_cookies(self, request):
        if self.cookies is None:
            cookies_dict = {}
        else:
            cookies_dict = self.cookies
        cookies_string = "; ".join([f"{k}={v}" for k, v in cookies_dict.items()])
        request["cookies"] = cookies_string