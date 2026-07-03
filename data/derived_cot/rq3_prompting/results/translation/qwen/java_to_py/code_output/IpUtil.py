import socket
from typing import Optional

class IpUtil:
    @staticmethod
    def is_valid_ipv4(ip_address: str) -> bool:
        try:
            socket.getaddrinfo(ip_address, 0)
            return '.' in ip_address and ':' not in ip_address
        except socket.gaierror:
            return False

    @staticmethod
    def is_valid_ipv6(ip_address: str) -> bool:
        try:
            socket.getaddrinfo(ip_address, 0)
            return ':' in ip_address
        except socket.gaierror:
            return False

    @staticmethod
    def get_hostname(ip_address: str) -> Optional[str]:
        try:
            if ip_address == "0.0.0.0":
                return socket.getfqdn()
            
            addresses = socket.getaddrinfo(ip_address, 0, 0, 0, 0, socket.AI_CANONNAME)
            if not addresses:
                return None
            
            canonical_hostname = addresses[0][3]
            if canonical_hostname == ip_address:
                return None
            return canonical_hostname
        except socket.gaierror:
            return None