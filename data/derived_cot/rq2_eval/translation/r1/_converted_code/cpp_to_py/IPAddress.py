class IPAddress:
    def __init__(self, ip_address):
        self.ip_address = ip_address
        
    def is_valid(self):
        tokens = self.ip_address.split('.')
        if len(tokens) != 4:
            return False
        for octet in tokens:
            if not self.is_valid_octet(octet):
                return False
        return True
    
    def get_octets(self):
        if self.is_valid():
            return self.ip_address.split('.')
        else:
            return []
    
    def get_binary(self):
        if not self.is_valid():
            return ""
        octets = self.get_octets()
        binary_parts = []
        for octet in octets:
            num = int(octet)
            bin_str = bin(num)[2:]
            bin_str = bin_str.zfill(8)
            binary_parts.append(bin_str)
        return '.'.join(binary_parts)
    
    def is_valid_octet(self, octet):
        if len(octet) == 0 or len(octet) > 3:
            return False
        if not octet.isdigit():
            return False
        num = int(octet)
        if num < 0 or num > 255:
            return False
        return True