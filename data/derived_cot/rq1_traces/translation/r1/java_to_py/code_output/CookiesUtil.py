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
        if not os.path.exists(self.cookies_file):
            return {}
        try:
            with open(self.cookies_file, 'r') as file:
                cookies_data = json.load(file)
                if isinstance(cookies_data, dict):
                    return cookies_data
                else:
                    return {}
        except (IOError, json.JSONDecodeError):
            return {}

    def _save_cookies(self):
        if self.cookies is None:
            return False
        try:
            with open(self.cookies_file, 'w') as file:
                json.dump(self.cookies, file, indent=None)
            return True
        except IOError:
            return False

    def set_cookies(self, request):
        if self.cookies is None:
            request["cookies"] = ""
            return
        cookies_string = ""
        for key, value in self.cookies.items():
            if cookies_string:
                cookies_string += "; "
            cookies_string += f"{key}={value}"
        request["cookies"] = cookies_string