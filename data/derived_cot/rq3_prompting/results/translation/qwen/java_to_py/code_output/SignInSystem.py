class SignInSystem:
    def __init__(self):
        self.users = {}

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
        return all(status for status in self.users.values())

    def allNotSignedIn(self):
        return [username for username, status in self.users.items() if not status]