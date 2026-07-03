#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

bool isValidIpv4(const std::string& ipAddress) {
    struct addrinfo hints, *res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res);
    if (status != 0) {
        return false;
    }
    freeaddrinfo(res);
    return ipAddress.find('.') != std::string::npos &&
           ipAddress.find(':') == std::string::npos;
}

bool isValidIpv6(const std::string& ipAddress) {
    struct addrinfo hints, *res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res);
    if (status != 0) {
        return false;
    }
    freeaddrinfo(res);
    return ipAddress.find(':') != std::string::npos;
}

std::string getHostname(const std::string& ipAddress) {
    if (ipAddress == "0.0.0.0") {
        char hostname[256];
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            return std::string(hostname);
        }
        return "";
    }

    struct addrinfo hints, *res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res);
    if (status != 0) {
        return "";
    }

    char host[NI_MAXHOST];
    int ret = getnameinfo(res->ai_addr, res->ai_addrlen,
                          host, sizeof(host), nullptr, 0, NI_NAMEREQD);
    freeaddrinfo(res);
    if (ret != 0) {
        return "";
    }

    std::string hostname(host);
    if (hostname == ipAddress) {
        return "";
    }
    return hostname;
}