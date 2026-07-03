class SignInSystem:
    def __init__(self):
        self.users = {}  # Using a dictionary instead of HashMap

    def addUser(self, username):
        if username in self.users:
            return False
        self.users[username] = False
        return True

    def signIn(self, username):
        if username not in self.users:
            return False
        self.users[username] = True
        return True

    def checkSignIn(self, username):
        return self.users.get(username, False)

    def allSignedIn(self):
        return all(value for value in self.users.values())

    def allNotSignedIn(self):
        return [username for username, is_signed_in in self.users.items() if not is_signed_in]