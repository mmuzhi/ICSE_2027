from datetime import datetime
from collections import namedtuple
from typing import Dict, List, Optional, Tuple

Message = namedtuple('Message', ['sender', 'receiver', 'message', 'timestamp'])

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
        timestamp = self.get_current_time()
        new_message = Message(sender, receiver, message, timestamp)
        self.users[sender].append(new_message)
        self.users[receiver].append(new_message)
        return True

    def get_messages(self, username: str) -> List[Message]:
        return self.users.get(username, [])

    def get_users(self) -> Dict[str, List[Message]]:
        return {user: messages[:] for user, messages in self.users.items()}

    def get_current_time(self) -> str:
        now = datetime.now()
        return now.strftime("%Y-%m-%d %H:%M:%S")