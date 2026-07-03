import json

class CookiesUtil:
    def __init__(self, cookiesFile):
        self.cookiesFile = cookiesFile
        self.cookies = None

    def getCookies(self, response):
        self.cookies = response.get("cookies")
        self._saveCookies()

    def loadCookies(self):
        try:
            with open(self.cookiesFile, 'r') as reader:
                jsonObject = json.load(reader)
                cookiesData = {str(k): str(v) for k, v in jsonObject.items()}
                return cookiesData
        except (OSError, json.JSONDecodeError):
            return {}

    def _saveCookies(self):
        try:
            with open(self.cookiesFile, 'w') as file:
                obj = {}
                if self.cookies is not None:
                    obj = self.cookies
                json.dump(obj, file)
                file.flush()
            return True
        except OSError:
            return False

    def setCookies(self, request):
        cookiesString = "; ".join(
            f"{k}={v}" for k, v in (self.cookies or {}).items()
        )
        request["cookies"] = cookiesString