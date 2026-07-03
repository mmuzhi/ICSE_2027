import time
from typing import List, Optional

class User:
    def __init__(self, name: str = "", level: int = 0, address: str = ""):
        self.name = name
        self.level = level
        self.address = address

class Authorization:
    def __init__(self, user: Optional[User] = None, jwt: str = ""):
        self.user = user if user is not None else User()
        self.jwt = jwt

class Request:
    def __init__(self, path: str = "", method: str = "", auth: Optional[Authorization] = None):
        self.path = path
        self.method = method
        self.auth = auth if auth is not None else Authorization()

class AccessGatewayFilter:
    def __init__(self):
        pass

    def filter(self, request: Request) -> bool:
        request_uri = request.path
        # method is not used in the logic but kept for consistency with the C++ source
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

    def is_start_with(self, request_uri: str) -> bool:
        start_with = ["/api", "/login"]
        for s in start_with:
            if request_uri.startswith(s):
                return True
        return False

    def get_jwt_user(self, request: Request) -> Authorization:
        token = request.auth
        user = token.user

        if token.jwt.startswith(user.name):
            jwt_str_date = token.jwt[len(user.name):]
            try:
                jwt_timestamp = int(jwt_str_date)  # assume integer seconds since epoch
            except (ValueError, TypeError):
                return Authorization()  # failed parse -> empty authorization

            now = int(time.time())
            if (now - jwt_timestamp) >= 3 * 24 * 60 * 60:
                return Authorization()  # expired

        return token

    def set_current_user_info_and_log(self, user: User) -> None:
        print(f"{user.name} {user.address} {int(time.time())}")