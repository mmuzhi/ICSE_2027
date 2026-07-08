class IPAddress:
    def __init__(self, ip_address):
        self.ip_address = ip_address

    def is_valid(self):
        # Java's split("\\.") removes trailing empty strings by default.
        # Python's split(".") keeps them. We use rstrip('.') to exactly match Java's behavior.
        octets = self.ip_address.rstrip('.').split('.')
        
        if len(octets) != 4:
            return False
            
        for octet in octets:
            try:
                num = int(octet)
                if num < 0 or num > 255:
                    return False
            except ValueError:  # Equivalent to Java's NumberFormatException
                return False
                
        return True

    def get_octets(self):
        if self.is_valid():
            return self.ip_address.rstrip('.').split('.')
        return []

    def get_binary(self):
        if self.is_valid():
            octets = self.ip_address.rstrip('.').split('.')
            # format(num, '08b') replaces the clunky Java string formatting and parsing
            binary_octets = [format(int(octet), '08b') for octet in octets]
            return ".".join(binary_octets)
        return ""