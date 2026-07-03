class IPAddress:
    def __init__(self, ip_address: str):
        self.ip_address = ip_address

    def is_valid(self) -> bool:
        octets = self.ip_address.split('.')
        if len(octets) != 4:
            return False
        for octet in octets:
            if not self._is_valid_octet(octet):
                return False
        return True

    def get_octets(self) -> list[str]:
        if self.is_valid():
            return self.ip_address.split('.')
        return []

    def get_binary(self) -> str:
        if not self.is_valid():
            return ""
        octets = self.get_octets()
        binary_parts = []
        for num_str in octets:
            num = int(num_str)
            binary_parts.append(f"{num:08b}")
        return '.'.join(binary_parts)

    def _is_valid_octet(self, octet: str) -> bool:
        if octet == "" or len(octet) > 3:
            return False
        for char in octet:
            if not char.isdigit():
                return False
        try:
            num = int(octet)
        except ValueError:
            return False
        return 0 <= num <= 255