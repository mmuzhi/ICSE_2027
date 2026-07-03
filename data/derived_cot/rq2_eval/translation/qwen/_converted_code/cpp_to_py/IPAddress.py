class IPAddress:
    def __init__(self, ip_address: str):
        self.ip_address = ip_address

    def is_valid(self) -> bool:
        octets = self.ip_address.split('.')
        if len(octets) != 4:
            return False
        for octet in octets:
            if not self.is_valid_octet(octet):
                return False
        return True

    def get_octets(self) -> list:
        if self.is_valid():
            return self.ip_address.split('.')
        return []

    def get_binary(self) -> str:
        if self.is_valid():
            octets = self.get_octets()
            binary_parts = []
            for octet in octets:
                num = int(octet)
                binary_parts.append(bin(num)[2:].zfill(8))
            return '.'.join(binary_parts)
        return ''

    def is_valid_octet(self, octet: str) -> bool:
        if octet == "" or len(octet) > 3:
            return False
        if not octet.isdigit():
            return False
        num = int(octet)
        return 0 <= num <= 255