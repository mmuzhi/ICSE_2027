import time

class Message:
    def __init__(self, sender, receiver, message, timestamp):
        self.sender = sender
        self.receiver = receiver
        self.message = message
        self.timestamp = timestamp

class Chat:
    def __init__(self):
        self.users = {}
    
    def add_user(self, username):
        if username in self.users:
            return False
        self.users[username] = []
        return True
    
    def remove_user(self, username):
        if username in self.users:
            del self.users[username]
            return True
        return False
    
    def send_message(self, sender, receiver, message):
        if sender not in self.users or receiver not in self.users:
            return False
        timestamp = self.get_current_time()
        msg = Message(sender, receiver, message, timestamp)
        self.users[sender].append(msg)
        self.users[receiver].append(msg)
        return True
    
    def get_messages(self, username):
        if username not in self.users:
            return []
        return [Message(msg.sender, msg.receiver, msg.message, msg.timestamp) for msg in self.users[username]]
    
    def get_users(self):
        result = {}
        for user, messages in self.users.items():
            result[user] = [Message(msg.sender, msg.receiver, msg.message, msg.timestamp) for msg in messages]
        return result
    
    def get_current_time(self):
        return time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())