import socket

def is_valid_ipv4(ip_address):
    try:
        socket.getaddrinfo(ip_address, None, socket.AF_INET)
        if '.' in ip_address and ':' not in ip_address:
            return True
        else:
            return False
    except Exception:
        return False

def is_valid_ipv6(ip_address):
    try:
        socket.getaddrinfo(ip_address, None, socket.AF_INET6)
        if ':' in ip_address:
            return True
        else:
            return False
    except Exception:
        return False

def get_hostname(ip_address):
    if ip_address == "0.0.0.0":
        try:
            local_host = socket.getlocalhost()
            return local_host.getfqdn()
        except Exception:
            return None
    else:
        try:
            # Resolve the input to an address
            addr = socket.getaddrinfo(ip_address, None)[0][4][0]
            # Get the hostname for the resolved address
            hostname = socket.gethostbyaddr(addr)[0]
        except (socket.herror, socket.gaierror) as e:
            hostname = ip_address
        if hostname == ip_address:
            return None
        else:
            return hostname