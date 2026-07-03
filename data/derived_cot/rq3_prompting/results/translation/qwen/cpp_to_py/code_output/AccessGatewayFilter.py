import time

class User:
    def __init__(self, name, level, address):
        self.name = name
        self.level = level
        self.address = address

class Authorization:
    def __init__(self, user, jwt):
        self.user = user
        self.jwt = jwt

class Request:
    def __init__(self, path, method, auth):
        self.path = path
        self.method = method
        self.auth = auth

class AccessGatewayFilter:
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
        prefixes = ["/api", "/login"]
        for prefix in prefixes:
            if request_uri.startswith(prefix):
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
                return Authorization(None, None)

            now = time.time()
            if now - jwt_timestamp >= 3 * 24 * 60 * 60:
                return Authorization(None, None)
        
        return token

    def set_current_user_info_and_log(self, user):
        print(f"{user.name} {user.address} {time.time()}")