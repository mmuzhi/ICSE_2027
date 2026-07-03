import datetime

class EmailClient:

    def __init__(self, addr, capacity):
        self.addr = addr
        self.capacity = capacity
        self.inbox = []

    def send_to(self, recv, content, size):
        if not recv.isFullWithOneMoreEmail(size):
            timestamp = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            email = {'sender': self.addr, 'receiver': recv.addr, 'content': content, 'size': size, 'time': timestamp, 'state': 'unread'}
            recv.inbox.append(email)
            return True
        else:
            self.clear_inbox(size)
            if recv.isFullWithOneMoreEmail(size):
                return False
            return self.send_to(recv, content, size)

    def fetch(self):
        if not self.inbox:
            return None
        for email in self.inbox:
            if email['state'] == 'unread':
                email['state'] = 'read'
                return email
        return None

    def is_full_with_one_more_email(self, size):
        occupiedSize = self.get_occupied_size()
        return occupiedSize + size > self.capacity

    def get_occupied_size(self):
        occupiedSize = 0.0
        for email in self.inbox:
            size_val = email['size']
            occupiedSize += float(size_val)
        return occupiedSize

    def clear_inbox(self, size):
        if not self.addr:
            return
        freedSpace = 0.0
        while freedSpace < size and self.inbox:
            email = self.inbox.pop(0)
            freedSpace += float(email['size'])

    def getInbox(self):
        return self.inbox

    def setInbox(self, inbox):
        self.inbox = inbox