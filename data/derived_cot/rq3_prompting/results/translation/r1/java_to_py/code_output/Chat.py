from datetime import datetime
from typing import Dict, List


class Chat:
    class Message:
        def __init__(self, sender: str, receiver: str, message: str, timestamp: str):
            self._sender = sender
            self._receiver = receiver
            self._message = message
            self._timestamp = timestamp

        def get_sender(self) -> str:
            return self._sender

        def get_receiver(self) -> str:
            return self._receiver

        def get_message(self) -> str:
            return self._message

        def get_timestamp(self) -> str:
            return self._timestamp

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or type(other) is not type(self):
                return False
            return (self._sender == other._sender and
                    self._receiver == other._receiver and
                    self._message == other._message and
                    self._timestamp == other._timestamp)

        def __hash__(self):
            return hash((self._sender, self._receiver, self._message, self._timestamp))

        def __repr__(self):
            return (f"Message{{sender='{self._sender}', receiver='{self._receiver}', "
                    f"message='{self._message}', timestamp='{self._timestamp}'}}")

    def __init__(self):
        self._users: Dict[str, List[Chat.Message]] = {}

    def add_user(self, username: str) -> bool:
        if username in self._users:
            return False
        self._users[username] = []
        return True

    def remove_user(self, username: str) -> bool:
        if username in self._users:
            del self._users[username]
            return True
        return False

    def send_message(self, sender: str, receiver: str, message: str) -> bool:
        if sender not in self._users or receiver not in self._users:
            return False
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        msg = Chat.Message(sender, receiver, message, timestamp)
        self._users[sender].append(msg)
        self._users[receiver].append(msg)
        return True

    def get_messages(self, username: str) -> List[Message]:
        if username not in self._users:
            return []
        return self._users[username]

    def get_users(self) -> Dict[str, List[Message]]:
        return self._users