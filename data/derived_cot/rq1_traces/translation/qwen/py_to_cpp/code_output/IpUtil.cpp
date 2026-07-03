#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <optional>

namespace IpUtil {

    static bool is_valid_ipv4(const std::string& ip_address) {
        struct sockaddr_in sa;
        return (inet_pton(AF_INET, ip_address.c_str(), &(sa.sin_addr)) == 1);
    }

    static bool is_valid_ipv6(const std::string& ip_address) {
        struct sockaddr_in6 sa;
        return (inet_pton(AF_INET6, ip_address.c_str(), &(sa.sin6_addr)) == 1);
    }

    static std::optional<std::string> get_hostname(const std::string& ip_address) {
        struct sockaddr_in sa4;
        if (inet_pton(AF_INET, ip_address.c_str(), &(sa4.sin_addr)) == 1) {
            struct hostent* host_entry = gethostbyaddr(&sa4.sin_addr, sizeof(sa4.sin_addr), AF_INET);
            if (host_entry) {
                return std::string(host_entry->h_name);
            }
            return std::nullopt;
        }

        struct sockaddr_in6 sa6;
        if (inet_pton(AF_INET6, ip_address.c_str(), &(sa6.sin6_addr)) == 1) {
            return std::nullopt;
        }

        return std::nullopt;
    }

}