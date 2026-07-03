import datetime
from typing import Dict, List

class Chat:

    class Message:
        __slots__ = ['_sender', '_receiver', '_message', '_timestamp']

        def __init__(self, sender: str, receiver: str, message: str, timestamp: str) -> None:
            self._sender = sender
            self._receiver = receiver
            self._message = message
            self._timestamp = timestamp

        def getSender(self) -> str:
            return self._sender

        def getReceiver(self) -> str:
            return self._receiver

        def getMessage(self) -> str:
            return self._message

        def getTimestamp(self) -> str:
            return self._timestamp

        def __eq__(self, other: object) -> bool:
            if self is other:
                return True
            if other is None or type(self) != type(other):
                return False
            return self._sender == other._sender and self._receiver == other._receiver and (self._message == other._message) and (self._timestamp == other._timestamp)

        def __hash__(self) -> int:
            return hash((self._sender, self._receiver, self._message, self._timestamp))

        def __str__(self) -> str:
            return f"Message{{sender='{self._sender}', receiver='{self._receiver}', message='{self._message}', timestamp='{self._timestamp}'}}"

    def __init__(self) -> None:
        self.users: Dict[str, List['Chat.Message']] = {}

    def add_user(self, username: str) -> bool:
        if username in self.users:
            return False
        else:
            self.users[username] = []
            return True

    def remove_user(self, username: str) -> bool:
        if username in self.users:
            del self.users[username]
            return True
        else:
            return False

    def send_message(self, sender: str, receiver: str, message: str) -> bool:
        if sender not in self.users or receiver not in self.users:
            return False
        timestamp = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        message_info = Chat.Message(sender, receiver, message, timestamp)
        self.users[sender].append(message_info)
        self.users[receiver].append(message_info)
        return True

    def get_messages(self, username: str) -> List['Chat.Message']:
        if username not in self.users:
            return []
        return self.users[username]

    def getUsers(self) -> Dict[str, List['Chat.Message']]:
        return self.users