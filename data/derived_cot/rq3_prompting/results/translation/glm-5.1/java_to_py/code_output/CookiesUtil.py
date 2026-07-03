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
            with open(self.cookies_file, "r") as f:
                json_object = json.load(f)
                return {str(k): str(v) for k, v in json_object.items()}
        except (OSError, json.JSONDecodeError):
            return {}

    def _save_cookies(self):
        try:
            with open(self.cookies_file, "w") as f:
                json_object = {}
                if self.cookies is not None:
                    json_object.update(self.cookies)
                json.dump(json_object, f)
            return True
        except OSError:
            return False

    def set_cookies(self, request):
        if self.cookies is not None:
            cookies_string = "; ".join(
                f"{k}={v}" for k, v in self.cookies.items()
            )
        else:
            cookies_string = ""
        request["cookies"] = cookies_string