from datetime import datetime, date, timedelta

class AccessGatewayFilter:
    def filter(self, request):
        request_uri = request.get("path")
        method = request.get("method")

        if self.is_start_with(request_uri):
            return True

        try:
            token = self.get_jwt_user(request)
            user = token.get("user")
            if int(user.get("level")) > 2:
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
        headers = request.get("headers")
        auth_header = headers.get("Authorization")
        token = auth_header
        user = token.get("user")
        jwt = token.get("jwt")

        user_name = user.get("name")
        if jwt.startswith(user_name):
            date_str = jwt[len(user_name):]
            formatter = "%Y-%m-%d"
            jwt_date = datetime.strptime(date_str, formatter).date()
            today = date.today()
            three_days_ago = today - timedelta(days=3)
            if three_days_ago > jwt_date:
                return None
        return token

    def set_current_user_info_and_log(self, user):
        host = user.get("address")
        message = user.get("name") + host + date.today()
        print(message)