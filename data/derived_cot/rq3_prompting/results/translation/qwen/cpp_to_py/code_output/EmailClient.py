import time

class EmailClient:
    def __init__(self, addr, capacity):
        self.addr = addr
        self.capacity = capacity
        self.inbox = []

    def get_current_time(self):
        t = time.localtime()
        return f"{1900 + t.tm_year}-{1 + t.tm_mon}-{t.tm_mday} {t.tm_hour}:{t.tm_min}:{t.tm_sec}"

    def send_to(self, recv, content, size):
        if not recv.is_full_with_one_more_email(size):
            email = {
                "sender": self.addr,
                "receiver": recv.addr,
                "content": content,
                "size": str(size),
                "time": self.get_current_time(),
                "state": "unread"
            }
            recv.inbox.append(email)
            return True
        else:
            self.clear_inbox(size)
            return False

    def fetch(self):
        if not self.inbox:
            return {}
        for i, email in enumerate(self.inbox):
            if email["state"] == "unread":
                email["state"] = "read"
                return email
        return {}

    def is_full_with_one_more_email(self, size):
        return self.get_occupied_size() + size > self.capacity

    def get_occupied_size(self):
        return sum(int(email["size"]) for email in self.inbox)

    def clear_inbox(self, size):
        if not self.addr:
            return
        freed = 0
        while freed < size and self.inbox:
            email = self.inbox.pop(0)
            freed += int(email["size"])