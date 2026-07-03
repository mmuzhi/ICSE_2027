import socket

class IpUtil:
    @staticmethod
    def is_valid_ipv4(ip_address):
        try:
            socket.inet_pton(socket.AF_INET, ip_address)
            return True
        except:
            return False

    @staticmethod
    def is_valid_ipv6(ip_address):
        try:
            socket.inet_pton(socket.AF_INET6, ip_address)
            return True
        except:
            return False

    @staticmethod
    def get_hostname(ip_address):
        if ip_address == "0.0.0.0":
            try:
                return socket.gethostname()
            except:
                return ""
        
        try:
            return socket.gethostbyaddr(ip_address)[0]
        except:
            return ""