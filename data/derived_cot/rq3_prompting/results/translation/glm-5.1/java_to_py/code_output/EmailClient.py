import datetime
from typing import List, Dict, Optional, Any


class EmailClient:
    def __init__(self, addr: str, capacity: float):
        self.addr = addr
        self.capacity = capacity
        self.inbox: List[Dict[str, Any]] = []

    def sendTo(self, recv: "EmailClient", content: str, size: float) -> bool:
        if not recv.isFullWithOneMoreEmail(size):
            timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            email: Dict[str, Any] = {
                "sender": self.addr,
                "receiver": recv.addr,
                "content": content,
                "size": size,
                "time": timestamp,
                "state": "unread",
            }
            recv.inbox.append(email)
            return True
        else:
            self.clearInbox(size)
            if recv.isFullWithOneMoreEmail(size):
                return False
            return self.sendTo(recv, content, size)

    def fetch(self) -> Optional[Dict[str, Any]]:
        if not self.inbox:
            return None
        for email in self.inbox:
            if email.get("state") == "unread":
                email["state"] = "read"
                return email
        return None

    def isFullWithOneMoreEmail(self, size: float) -> bool:
        occupied_size = self.getOccupiedSize()
        return occupied_size + size > self.capacity

    def getOccupiedSize(self) -> float:
        occupied_size = 0.0
        for email in self.inbox:
            size_obj = email.get("size")
            if isinstance(size_obj, (int, float)):
                occupied_size += float(size_obj)
        return occupied_size

    def clearInbox(self, size: float) -> None:
        if self.addr == "":
            return
        freed_space = 0.0
        while freed_space < size and self.inbox:
            email = self.inbox.pop(0)
            size_obj = email.get("size")
            if isinstance(size_obj, (int, float)):
                freed_space += float(size_obj)

    def getInbox(self) -> List[Dict[str, Any]]:
        return self.inbox

    def setInbox(self, inbox: List[Dict[str, Any]]) -> None:
        self.inbox = inbox