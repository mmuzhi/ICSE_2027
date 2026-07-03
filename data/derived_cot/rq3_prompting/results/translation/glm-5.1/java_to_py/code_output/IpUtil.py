import socket

def isValidIpv4(ipAddress: str) -> bool:
    try:
        socket.getaddrinfo(ipAddress, None)
        return '.' in ipAddress and ':' not in ipAddress
    except socket.gaierror:
        return False

def isValidIpv6(ipAddress: str) -> bool:
    try:
        socket.getaddrinfo(ipAddress, None)
        return ':' in ipAddress
    except socket.gaierror:
        return False

def getHostname(ipAddress: str) -> str | None:
    try:
        if ipAddress == "0.0.0.0":
            return socket.gethostname()
        hostname = socket.gethostbyaddr(ipAddress)[0]
        if hostname == ipAddress:
            return None
        return hostname
    except (socket.gaierror, socket.herror):
        return None