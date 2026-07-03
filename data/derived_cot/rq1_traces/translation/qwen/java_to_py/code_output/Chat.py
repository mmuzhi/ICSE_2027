from datetime import datetime
from typing import List, Dict, Optional

class Message:
    def __init__(self, sender: str, receiver: str, message: str, timestamp: str):
        self.sender = sender
        self.receiver = receiver
        self.message = message
        self.timestamp = timestamp

    def __eq__(self, other):
        if not isinstance(other, Message):
            return False
        return (
            self.sender == other.sender and
            self.receiver == other.receiver and
            self.message == other.message and
            self.timestamp == other.timestamp
        )

    def __hash__(self):
        return hash((self.sender, self.receiver, self.message, self.timestamp))

    def __repr__(self):
        return (f"Message(sender='{self.sender}', receiver='{self.receiver}', "
                f"message='{self.message}', timestamp='{self.timestamp}')")

class Chat:
    def __init__(self):
        self.users: Dict[str, List[Message]] = {}

    def add_user(self, username: str) -> bool:
        if username in self.users:
            return False
        self.users[username] = []
        return True

    def remove_user(self, username: str) -> bool:
        if username in self.users:
            del self.users[username]
            return True
        return False

    def send_message(self, sender: str, receiver: str, message: str) -> bool:
        if sender not in self.users or receiver not in self.users:
            return False
        
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        msg = Message(sender, receiver, message, timestamp)
        
        self.users[sender].append(msg)
        self.users[receiver].append(msg)
        return True

    def get_messages(self, username: str) -> List[Message]:
        return self.users.get(username, [])

    def get_users(self) -> Dict[str, List[Message]]:
        return self.users.copy()