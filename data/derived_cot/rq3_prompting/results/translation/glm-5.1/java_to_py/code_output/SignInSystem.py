class SignInSystem:
    def __init__(self):
        self.users = {}

    def addUser(self, username):
        if username in self.users:
            return False
        else:
            self.users[username] = False
            return True

    def signIn(self, username):
        if username not in self.users:
            return False
        else:
            self.users[username] = True
            return True

    def checkSignIn(self, username):
        if username not in self.users:
            return False
        else:
            return self.users[username]

    def allSignedIn(self):
        for signed_in in self.users.values():
            if not signed_in:
                return False
        return True

    def allNotSignedIn(self):
        notSignedInUsers = []
        for key, value in self.users.items():
            if not value:
                notSignedInUsers.append(key)
        return notSignedInUsers