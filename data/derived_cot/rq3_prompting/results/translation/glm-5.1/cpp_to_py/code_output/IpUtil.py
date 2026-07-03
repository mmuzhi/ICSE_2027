import socket
import ipaddress

class IpUtil:
    @staticmethod
    def is_valid_ipv4(ip_address: str) -> bool:
        try:
            ipaddress.IPv4Address(ip_address)
            return True
        except ValueError:
            return False

    @staticmethod
    def is_valid_ipv6(ip_address: str) -> bool:
        try:
            ipaddress.IPv6Address(ip_address)
            return True
        except ValueError:
            return False

    @staticmethod
    def get_hostname(ip_address: str) -> str:
        if ip_address == "0.0.0.0":
            try:
                return socket.gethostname()
            except Exception:
                return ""
        
        try:
            # getnameinfo with flags=0 mirrors the C++ getnameinfo default behavior,
            # returning the hostname if available, or the IP address itself if not.
            host, _ = socket.getnameinfo((ip_address, 0), 0)
            return host
        except Exception:
            return ""