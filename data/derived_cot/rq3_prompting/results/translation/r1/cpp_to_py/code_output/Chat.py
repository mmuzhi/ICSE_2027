from datetime import datetime
import copy


class Chat:
    class Message:
        def __init__(self, sender: str, receiver: str, message: str, timestamp: str):
            self.sender = sender
            self.receiver = receiver
            self.message = message
            self.timestamp = timestamp

    def __init__(self):
        self.users = {}  # dict[str, list[Message]]

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
        msg = Chat.Message(sender, receiver, message, timestamp)
        self.users[sender].append(msg)
        self.users[receiver].append(msg)
        return True

    def get_messages(self, username: str):
        if username not in self.users:
            return []
        # Return a deep copy of the list and each Message to preserve value semantics.
        return [copy.deepcopy(m) for m in self.users[username]]

    def get_users(self):
        # Return a deep copy of the entire map.
        return {
            user: [copy.deepcopy(m) for m in msgs]
            for user, msgs in self.users.items()
        }

    def get_current_time(self) -> str:
        return datetime.now().strftime("%Y-%m-%d %H:%M:%S")