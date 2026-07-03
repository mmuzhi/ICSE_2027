import datetime

class Chat:
    class Message:
        def __init__(self, sender, receiver, message, timestamp):
            self.sender = sender
            self.receiver = receiver
            self.message = message
            self.timestamp = timestamp

        def __eq__(self, obj):
            if self is obj:
                return True
            if obj is None or not isinstance(obj, self.__class__):
                return False
            return (self.sender == obj.sender and
                    self.receiver == obj.receiver and
                    self.message == obj.message and
                    self.timestamp == obj.timestamp)

        def __hash__(self):
            return hash((self.sender, self.receiver, self.message, self.timestamp))

        def __repr__(self):
            return f"Message{{sender='{self.sender}', receiver='{self.receiver}', message='{self.message}', timestamp='{self.timestamp}'}}"

    def __init__(self):
        self.users = {}

    def addUser(self, username):
        if username in self.users:
            return False
        else:
            self.users[username] = []
            return True

    def removeUser(self, username):
        if username in self.users:
            del self.users[username]
            return True
        else:
            return False

    def sendMessage(self, sender, receiver, message):
        if sender not in self.users or receiver not in self.users:
            return False

        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        message_info = self.Message(sender, receiver, message, timestamp)

        self.users[sender].append(message_info)
        self.users[receiver].append(message_info)
        return True

    def getMessages(self, username):
        if username not in self.users:
            return []
        return self.users[username]

    def getUsers(self):
        return self.users