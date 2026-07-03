class IPAddress:
    def __init__(self, ip_address):
        self.ip_address = ip_address

    def isValid(self):
        # Mimic Java's split("\\.") behavior which trims trailing empty strings
        octets = self.ip_address.split('.')
        while octets and octets[-1] == '':
            octets.pop()
            
        if len(octets) != 4:
            return False
            
        for octet in octets:
            # Mimic Java's Integer.parseInt strictly rejecting non-ASCII digits or signs
            if not octet or any(c < '0' or c > '9' for c in octet):
                return False
            num = int(octet)
            if num < 0 or num > 255:
                return False
                
        return True

    def getOctets(self):
        if self.isValid():
            octets = self.ip_address.split('.')
            while octets and octets[-1] == '':
                octets.pop()
            return octets
        return []

    def getBinary(self):
        if self.isValid():
            octets = self.ip_address.split('.')
            while octets and octets[-1] == '':
                octets.pop()
            binary_octets = [format(int(octet), '08b') for octet in octets]
            return ".".join(binary_octets)
        return ""