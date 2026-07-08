import json


class CookiesUtil:
    def __init__(self, cookies_file):
        self.cookies_file = cookies_file
        self.cookies = None

    def get_cookies(self, response):
        self.cookies = response.get("cookies")
        self._save_cookies()

    def load_cookies(self):
        try:
            with open(self.cookies_file, 'r') as reader:
                json_object = json.load(reader)
                cookies_data = {}
                for key, value in json_object.items():
                    cookies_data[key] = value
                return cookies_data
        except (OSError, json.JSONDecodeError):
            return {}

    def _save_cookies(self):
        try:
            with open(self.cookies_file, 'w') as file:
                json_object = {}
                if self.cookies is not None:
                    json_object.update(self.cookies)
                file.write(json.dumps(json_object, separators=(',', ':')))
                file.flush()
                return True
        except OSError:
            return False

    def set_cookies(self, request):
        cookies_string = ""
        if self.cookies is not None:
            parts = []
            for key, value in self.cookies.items():
                parts.append(f"{key}={value}")
            cookies_string = "; ".join(parts)
        request["cookies"] = cookies_string