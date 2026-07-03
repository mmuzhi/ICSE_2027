import time

class User:
    def __init__(self, name="", level=0, address=""):
        self.name = name
        self.level = level
        self.address = address

class Authorization:
    def __init__(self, user=None, jwt=""):
        if user is None:
            user = User()
        self.user = user
        self.jwt = jwt

class Request:
    def __init__(self, path="", method="", auth=None):
        self.path = path
        self.method = method
        if auth is None:
            auth = Authorization()
        self.auth = auth

class AccessGatewayFilter:
    def __init__(self):
        pass

    def filter(self, request):
        request_uri = request.path
        method = request.method

        if self.is_start_with(request_uri):
            return True

        try:
            token = self.get_jwt_user(request)
            user = token.user
            if user.level > 2:
                self.set_current_user_info_and_log(user)
                return True
        except Exception:
            return False
        return False

    def is_start_with(self, request_uri):
        start_with = ["/api", "/login"]
        for s in start_with:
            if request_uri.startswith(s):
                return True
        return False

    def get_jwt_user(self, request):
        token = request.auth
        user = token.user

        if token.jwt.startswith(user.name):
            jwt_str_date = token.jwt[len(user.name):]
            try:
                jwt_timestamp = int(jwt_str_date)
            except ValueError:
                return Authorization()

            now = time.time()
            if now - jwt_timestamp >= 3 * 24 * 60 * 60:
                return Authorization()
        return token

    def set_current_user_info_and_log(self, user):
        current_time = int(time.time())
        print(f"{user.name} {user.address} {current_time}")