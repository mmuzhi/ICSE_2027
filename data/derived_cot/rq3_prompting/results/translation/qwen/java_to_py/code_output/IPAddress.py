class IPAddress:
    def __init__(self, ip_address):
        self.ip_address = ip_address

    def isValid(self):
        parts = self.ip_address.split('.')
        if len(parts) != 4:
            return False
        for part in parts:
            try:
                num = int(part)
                if num < 0 or num > 255:
                    return False
            except ValueError:
                return False
        return True

    def getOctets(self):
        if not self.isValid():
            return []
        return self.ip_address.split('.')

    def getBinary(self):
        if not self.isValid():
            return ""
        parts = self.ip_address.split('.')
        binary_parts = [format(int(part), '08d') for part in parts]
        return '.'.join(binary_parts)