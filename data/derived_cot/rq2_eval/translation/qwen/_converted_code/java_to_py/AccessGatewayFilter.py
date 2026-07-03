from datetime import date, timedelta
from typing import Dict, Optional

class AccessGatewayFilter:

    def filter(self, request: Dict) -> bool:
        request_uri = request.get("path")
        method = request.get("method")

        if self.is_start_with(request_uri):
            return True

        try:
            token = self.get_jwt_user(request)
            if token is None:
                return False

            user = token.get("user")
            if user is None:
                return False

            level = user.get("level")
            if not isinstance(level, int):
                return False

            if level > 2:
                self.set_current_user_info_and_log(user)
                return True

        except Exception:
            return False

        return False

    def is_start_with(self, request_uri: str) -> bool:
        prefixes = ["/api", "/login"]
        for prefix in prefixes:
            if request_uri.startswith(prefix):
                return True
        return False

    def get_jwt_user(self, request: Dict) -> Optional[Dict]:
        headers = request.get("headers")
        if headers is None:
            raise Exception("Headers missing")

        auth_header = headers.get("Authorization")
        if auth_header is None:
            raise Exception("Authorization header missing")

        if not isinstance(auth_header, dict):
            raise Exception("Authorization header must be a dictionary")

        token = auth_header.get("user")
        if token is None:
            raise Exception("User not found in token")

        if not isinstance(token, dict):
            raise Exception("User must be a dictionary")

        jwt = token.get("jwt")
        if jwt is None:
            raise Exception("JWT not found in token")

        if not isinstance(jwt, str):
            raise Exception("JWT must be a string")

        user_name = token.get("name")
        if user_name is None:
            raise Exception("Name not found in user")

        if not isinstance(user_name, str):
            raise Exception("Name must be a string")

        if not jwt.startswith(user_name):
            return auth_header

        try:
            jwt_str_date = jwt[len(user_name):]
            jwt_date = date.strptime(jwt_str_date, "%Y-%m-%d")
        except Exception as e:
            raise Exception("Invalid date format in JWT")

        if date.today() - timedelta(days=3) > jwt_date:
            return None

        return auth_header

    def set_current_user_info_and_log(self, user: Dict):
        name = user.get("name")
        address = user.get("address")
        if name is None or address is None:
            raise Exception("Name or address not found in user")

        message = f"{name}{address}{date.today()}"
        print(message)