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
        for signedIn in self.users.values():
            if not signedIn:
                return False
        return True

    def all_not_signed_in(self):
        notSignedInUsers = []
        for username, signedIn in self.users.items():
            if not signedIn:
                notSignedInUsers.append(username)
        return notSignedInUsers