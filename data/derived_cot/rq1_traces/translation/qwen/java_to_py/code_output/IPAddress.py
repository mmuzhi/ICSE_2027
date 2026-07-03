class IPAddress:
    def __init__(self, ipAddress):
        self.ipAddress = ipAddress

    def isValid(self):
        octets = self.ipAddress.split('.')
        if len(octets) != 4:
            return False
        for octet in octets:
            try:
                num = int(octet)
                if num < 0 or num > 255:
                    return False
            except ValueError:
                return False
        return True

    def getOctets(self):
        if self.isValid():
            return self.ipAddress.split('.')
        return []

    def getBinary(self):
        if self.isValid():
            parts = []
            for octet in self.ipAddress.split('.'):
                num = int(octet)
                binary_str = bin(num)[2:].zfill(8)
                parts.append(binary_str)
            return '.'.join(parts)
        return ""