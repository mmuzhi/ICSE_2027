from datetime import datetime, timedelta

class AccessGatewayFilter:
    def __init__(self):
        pass

    def filter(self, request):
        request_uri = request.get("path")
        # method is extracted but not used in the original logic
        # method = request.get("method")

        if self.isStartWith(request_uri):
            return True

        try:
            token = self.getJwtUser(request)
            user = token["user"]
            if int(user["level"]) > 2:
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
        headers = request["headers"]
        token = headers["Authorization"]
        user = token["user"]
        jwt = token["jwt"]

        if jwt.startswith(user["name"]):
            jwt_str_date = jwt[len(user["name"]):]
            jwt_date = datetime.strptime(jwt_str_date, "%Y-%m-%d")
            if (datetime.now() - timedelta(days=3)).date() > jwt_date.date():
                return None
        return token

    def setCurrentUserInfoAndLog(self, user):
        host = user["address"]
        message = str(user["name"]) + host + str(datetime.today().date())
        print(message)