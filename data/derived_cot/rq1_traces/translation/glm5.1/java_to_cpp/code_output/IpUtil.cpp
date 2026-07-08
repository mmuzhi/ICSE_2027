#pragma once

#include <string>
#include <optional>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#ifndef NI_MAXHOST
#define NI_MAXHOST 1025
#endif

namespace org::example {

class IpUtil {
private:
    static void ensureWinsockInit() {
#ifdef _WIN32
        static struct Init {
            Init() {
                WSADATA wsaData;
                WSAStartup(MAKEWORD(2, 2), &wsaData);
            }
            ~Init() {
                WSACleanup();
            }
        } init;
#endif
    }

public:
    static bool isValidIpv4(const std::string& ipAddress) {
        ensureWinsockInit();

        struct addrinfo hints{}, *result = nullptr;
        hints.ai_family = AF_UNSPEC;

        int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &result);
        if (status != 0) {
            return false;
        }
        freeaddrinfo(result);

        return ipAddress.find('.') != std::string::npos
            && ipAddress.find(':') == std::string::npos;
    }

    static bool isValidIpv6(const std::string& ipAddress) {
        ensureWinsockInit();

        struct addrinfo hints{}, *result = nullptr;
        hints.ai_family = AF_UNSPEC;

        int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &result);
        if (status != 0) {
            return false;
        }
        freeaddrinfo(result);

        return ipAddress.find(':') != std::string::npos;
    }

    static std::optional<std::string> getHostname(const std::string& ipAddress) {
        ensureWinsockInit();

        if (ipAddress == "0.0.0.0") {
            char hostname[256];
            if (gethostname(hostname, sizeof(hostname)) == 0) {
                return std::string(hostname);
            }
            return std::nullopt;
        }

        struct addrinfo hints{}, *result = nullptr;
        hints.ai_family = AF_UNSPEC;

        int status = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &result);
        if (status != 0) {
            return std::nullopt;
        }

        char host[NI_MAXHOST];
        status = getnameinfo(result->ai_addr, result->ai_addrlen,
                             host, sizeof(host), nullptr, 0, 0);
        freeaddrinfo(result);

        if (status != 0) {
            return std::nullopt;
        }

        std::string hostname(host);
        if (hostname == ipAddress) {
            return std::nullopt;
        }
        return hostname;
    }
};

} // namespace org::example