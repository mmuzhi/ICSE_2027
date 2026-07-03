class IPAddress:
    def __init__(self, ip_address):
        self.ip_address = ip_address

    def is_valid(self):
        octets = self.ip_address.split('.')
        if len(octets) != 4:
            return False
        for octet in octets:
            if not self._is_valid_octet(octet):
                return False
        return True

    def get_octets(self):
        if self.is_valid():
            return self.ip_address.split('.')
        else:
            return []

    def get_binary(self):
        if self.is_valid():
            octets = self.get_octets()
            parts = []
            for i, octet in enumerate(octets):
                num = int(octet)
                if i > 0:
                    parts.append('.')
                parts.append(format(num, '08b'))
            return ''.join(parts)
        else:
            return ""

    def _is_valid_octet(self, octet):
        if not octet or len(octet) > 3:
            return False
        for c in octet:
            if not ('0' <= c <= '9'):
                return False
        value = int(octet)
        return 0 <= value <= 255