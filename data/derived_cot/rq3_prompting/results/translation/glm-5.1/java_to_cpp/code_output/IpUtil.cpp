#pragma once

#include <string>
#include <optional>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#endif

class IpUtil {
public:
    static bool isValidIpv4(const std::string& ipAddress) {
        struct addrinfo hints{}, *res;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res);
        if (status != 0) return false;
        freeaddrinfo(res);

        return ipAddress.find('.') != std::string::npos &&
               ipAddress.find(':') == std::string::npos;
    }

    static bool isValidIpv6(const std::string& ipAddress) {
        struct addrinfo hints{}, *res;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res);
        if (status != 0) return false;
        freeaddrinfo(res);

        return ipAddress.find(':') != std::string::npos;
    }

    static std::optional<std::string> getHostname(const std::string& ipAddress) {
        if (ipAddress == "0.0.0.0") {
            char hostname[256];
            if (gethostname(hostname, sizeof(hostname)) != 0) {
                return std::nullopt;
            }
            return std::string(hostname);
        }

        struct addrinfo hints{}, *res;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res);
        if (status != 0) return std::nullopt;

        char host[NI_MAXHOST];
        status = getnameinfo(res->ai_addr, res->ai_addrlen, host, sizeof(host), nullptr, 0, 0);
        freeaddrinfo(res);

        if (status != 0) return std::nullopt;

        std::string hostname(host);
        if (hostname == ipAddress) return std::nullopt;
        return hostname;
    }
};