class SignInSystem:
    def __init__(self):
        self.users = {}

    def add_user(self, username):
        if username in self.users:
            return False
        else:
            self.users[username] = False
            return True

    def sign_in(self, username):
        if username not in self.users:
            return False
        else:
            self.users[username] = True
            return True

    def check_sign_in(self, username):
        if username not in self.users:
            return False
        else:
            return self.users[username]

    def all_signed_in(self):
        for value in self.users.values():
            if not value:
                return False
        return True

    def all_not_signed_in(self):
        return [username for username, value in self.users.items() if not value]