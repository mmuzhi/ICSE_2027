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
        if username not in self.users:
            return False
        return self.users[username]

    def all_signed_in(self):
        for status in self.users.values():
            if not status:
                return False
        return True

    def all_not_signed_in(self):
        return [username for username, status in self.users.items() if not status]