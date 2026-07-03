#ifndef IP_UTIL_H
#define IP_UTIL_H

#include <string>
#include <optional>
#include <arpa/inet.h>
#include <netdb.h>

class IpUtil {
public:
    static bool is_valid_ipv4(const std::string& ip_address) {
        struct in_addr addr;
        return inet_pton(AF_INET, ip_address.c_str(), &addr) == 1;
    }

    static bool is_valid_ipv6(const std::string& ip_address) {
        struct in6_addr addr;
        return inet_pton(AF_INET6, ip_address.c_str(), &addr) == 1;
    }

    static std::optional<std::string> get_hostname(const std::string& ip_address) {
        struct in_addr addr;
        if (inet_pton(AF_INET, ip_address.c_str(), &addr) != 1) {
            return std::nullopt;
        }
        struct hostent* host = gethostbyaddr(&addr, sizeof(addr), AF_INET);
        if (host == nullptr) {
            return std::nullopt;
        }
        return std::string(host->h_name);
    }
};

#endif // IP_UTIL_H