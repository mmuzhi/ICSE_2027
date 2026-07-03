class SignInSystem:
    def __init__(self):
        self.users = {}

    def add_user(self, username: str) -> bool:
        if username in self.users:
            return False
        self.users[username] = False
        return True

    def sign_in(self, username: str) -> bool:
        if username not in self.users:
            return False
        self.users[username] = True
        return True

    def check_sign_in(self, username: str) -> bool:
        if username not in self.users:
            return False
        return self.users[username]

    def all_signed_in(self) -> bool:
        return all(status for status in self.users.values())

    def all_not_signed_in(self) -> list:
        return [user for user, signed in self.users.items() if not signed]