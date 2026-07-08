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
        else:
            return []

    def get_binary(self) -> str:
        if self.is_valid():
            octets = self.get_octets()
            # Convert each octet to its 8-bit zero-padded binary string representation
            binary_octets = [format(int(octet), '08b') for octet in octets]
            return '.'.join(binary_octets)
        else:
            return ""

    def _is_valid_octet(self, octet: str) -> bool:
        if not octet or len(octet) > 3:
            return False
        
        # Replicating C++ isdigit behavior strictly for ASCII digits
        if not all('0' <= c <= '9' for c in octet):
            return False
        
        value = int(octet)
        return 0 <= value <= 255