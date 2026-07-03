class IPAddress:
    def __init__(self, ip_address):
        self.ip_address = ip_address

    def isValid(self):
        octets = self.ip_address.split('.')
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
            return self.ip_address.split('.')
        else:
            return []

    def getBinary(self):
        if self.isValid():
            octets = self.ip_address.split('.')
            binary_octets = []
            for octet in octets:
                num = int(octet)
                bin_str = bin(num)[2:]
                padded_bin = bin_str.zfill(8)
                binary_octets.append(padded_bin)
            return ".".join(binary_octets)
        else:
            return ""