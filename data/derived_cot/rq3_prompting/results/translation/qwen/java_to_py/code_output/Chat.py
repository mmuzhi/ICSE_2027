from datetime import datetime

class Message:
    def __init__(self, sender, receiver, message, timestamp):
        self.sender = sender
        self.receiver = receiver
        self.message = message
        self.timestamp = timestamp

    def get_sender(self):
        return self.sender

    def get_receiver(self):
        return self.receiver

    def get_message(self):
        return self.message

    def get_timestamp(self):
        return self.timestamp

    def __eq__(self, other):
        if not isinstance(other, Message):
            return False
        return (self.sender == other.sender and
                self.receiver == other.receiver and
                self.message == other.message and
                self.timestamp == other.timestamp)

    def __hash__(self):
        return hash((self.sender, self.receiver, self.message, self.timestamp))

    def __str__(self):
        return (f"Message{{sender='{self.sender}', receiver='{self.receiver}', "
                f"message='{self.message}', timestamp='{self.timestamp}'}}")

class Chat:
    def __init__(self):
        self.users = {}

    def addUser(self, username):
        if username in self.users:
            return False
        self.users[username] = []
        return True

    def removeUser(self, username):
        if username in self.users:
            del self.users[username]
            return True
        return False

    def sendMessage(self, sender, receiver, message):
        if sender not in self.users or receiver not in self.users:
            return False
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        message_info = Message(sender, receiver, message, timestamp)
        self.users[sender].append(message_info)
        self.users[receiver].append(message_info)
        return True

    def getMessages(self, username):
        if username in self.users:
            return self.users[username]
        return []

    def getUsers(self):
        return self.users