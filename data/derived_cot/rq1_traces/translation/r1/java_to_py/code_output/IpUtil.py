import socket

def isValidIpv4(ipAddress):
    try:
        socket.getaddrinfo(ipAddress, None)
    except socket.gaierror:
        return False
    return ('.' in ipAddress) and (':' not in ipAddress)

def isValidIpv6(ipAddress):
    try:
        socket.getaddrinfo(ipAddress, None)
    except socket.gaierror:
        return False
    return ':' in ipAddress

def getHostname(ipAddress):
    if ipAddress == "0.0.0.0":
        try:
            return socket.gethostname()
        except OSError:
            return None
            
    try:
        hostname0 = socket.gethostbyaddr(ipAddress)[0]
    except OSError:
        return None
        
    try:
        hostname1, _, _ = socket.gethostbyname_ex(hostname0)
        canonical = hostname1
    except OSError:
        canonical = hostname0
        
    if canonical == ipAddress:
        return None
    else:
        return canonical