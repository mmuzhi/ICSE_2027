class SignInSystem:

    def __init__(self):
        self.users = {}

    def add_user(self, username):
        if username in self.users:
            return False
        self.users[username] = False
        return True

    def sign_in(self, username):
        if username not in self.users:
            return False
        self.users[username] = True
        return True

    def check_sign_in(self, username):
        return self.users.get(username, False)

    def all_signed_in(self):
        return all((value for value in self.users.values()))

    def all_not_signed_in(self):
        return [username for username, is_signed_in in self.users.items() if not is_signed_in]