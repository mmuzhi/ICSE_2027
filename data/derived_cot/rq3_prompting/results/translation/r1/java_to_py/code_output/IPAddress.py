class IPAddress:
    def __init__(self, ip_address: str):
        self.ip_address = ip_address

    def is_valid(self) -> bool:
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

    def get_octets(self) -> list:
        if self.is_valid():
            return self.ip_address.split('.')
        return []

    def get_binary(self) -> str:
        if self.is_valid():
            parts = []
            for octet in self.ip_address.split('.'):
                num = int(octet)
                parts.append(f"{num:08b}")
            return '.'.join(parts)
        return ""