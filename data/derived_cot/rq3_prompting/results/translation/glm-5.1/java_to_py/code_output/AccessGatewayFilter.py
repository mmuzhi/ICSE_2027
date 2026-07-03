from datetime import date, timedelta, datetime


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
            user = token.get("user")
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
        token = request.get("headers").get("Authorization")
        user = token.get("user")
        jwt = token.get("jwt")

        if jwt.startswith(user.get("name")):
            jwt_str_date = jwt[len(user.get("name")):]
            jwt_date = datetime.strptime(jwt_str_date, "%Y-%m-%d").date()
            if (date.today() - timedelta(days=3)) > jwt_date:
                return None
        return token

    def setCurrentUserInfoAndLog(self, user):
        host = user.get("address")
        message = str(user.get("name")) + str(host) + str(date.today())
        print(message)