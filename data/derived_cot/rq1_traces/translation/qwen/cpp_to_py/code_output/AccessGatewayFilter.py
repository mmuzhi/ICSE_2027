import datetime
import re

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
            pass
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
                # Assuming the date string is a Unix timestamp
                jwt_timestamp = int(jwt_str_date)
                expiration = datetime.datetime.fromtimestamp(jwt_timestamp)
            except (ValueError, OverflowError):
                raise Exception("Invalid JWT timestamp")
            except Exception as e:
                raise Exception(f"Error parsing JWT timestamp: {e}")

            current_time = datetime.datetime.now()
            if (current_time - expiration).total_seconds() >= 3 * 24 * 60 * 60:
                raise Exception("JWT expired")

        return token

    def set_current_user_info_and_log(self, user):
        print(f"{user.name} {user.address} {datetime.datetime.now().timestamp()}")

# Example usage:
if __name__ == "__main__":
    # Create a user
    user = User(name="test_user", level=3, address="123 Main St")
    
    # Create an authorization token
    auth = Authorization(user=user, jwt=f"{user.name}1234567890")
    
    # Create a request
    request = Request(path="/protected", method="GET", auth=auth)
    
    # Initialize the filter
    filter = AccessGatewayFilter()
    
    # Filter the request
    print("Filter result:", filter.filter(request))