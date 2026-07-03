from datetime import datetime, timedelta, date

class AccessGatewayFilter:
    def __init__(self):
        pass

    def filter(self, request):
        request_uri = request.get("path")
        method = request.get("method")

        if self.isStartWith(request_uri):
            return True

        try:
            token = self.getJwtUser(request)
            if token is None:
                return False
            user = token.get("user")
            if user is None:
                return False
            if user.get("level") > 2:
                self.setCurrentUserInfoAndLog(user)
                return True
        except Exception:
            return False
        return False

    def isStartWith(self, request_uri):
        start_with = ["/api", "/login"]
        for s in start_with:
            if request_uri.startswith(s):
                return True
        return False

    def getJwtUser(self, request):
        headers = request.get("headers")
        if headers is None:
            return None
        token = headers.get("Authorization")
        if token is None:
            return None
        user = token.get("user")
        jwt_str = token.get("jwt")
        if user is None or jwt_str is None:
            return token

        user_name = user.get("name")
        if user_name is None:
            return token

        if jwt_str.startswith(user_name):
            jwt_date_str = jwt_str[len(user_name):]
            try:
                jwt_date = datetime.strptime(jwt_date_str, "%Y-%m-%d").date()
            except ValueError:
                return token
            if date.today() - timedelta(days=3) > jwt_date:
                return None
        return token

    def setCurrentUserInfoAndLog(self, user):
        host = user.get("address", "")
        user_name = user.get("name", "")
        today = date.today().strftime("%Y-%m-%d")
        message = f"{user_name}{host}{today}"
        print(message)