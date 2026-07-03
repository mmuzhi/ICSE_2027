import socket


class IpUtil:
    @staticmethod
    def isValidIpv4(ipAddress):
        try:
            socket.getaddrinfo(ipAddress, None)
            return "." in ipAddress and ":" not in ipAddress
        except (socket.gaierror, OSError):
            return False

    @staticmethod
    def isValidIpv6(ipAddress):
        try:
            socket.getaddrinfo(ipAddress, None)
            return ":" in ipAddress
        except (socket.gaierror, OSError):
            return False

    @staticmethod
    def getHostname(ipAddress):
        try:
            if ipAddress == "0.0.0.0":
                return socket.gethostname()

            # Resolve the input to an IP address
            addrinfo = socket.getaddrinfo(ipAddress, None)
            for family, type, proto, canonname, sockaddr in addrinfo:
                ip = sockaddr[0]
                break

            # Reverse lookup the obtained IP
            hostname, aliaslist, ipaddrlist = socket.gethostbyaddr(ip)

            if hostname == ipAddress:
                return None
            return hostname
        except (socket.gaierror, socket.herror, OSError):
            return None