#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>
#include <optional>

class IpUtil {
public:
    static bool is_valid_ipv4(const std::string& ip_address) {
        struct sockaddr_in sa;
        return inet_pton(AF_INET, ip_address.c_str(), &(sa.sin_addr)) == 1;
    }

    static bool is_valid_ipv6(const std::string& ip_address) {
        struct sockaddr_in6 sa6;
        return inet_pton(AF_INET6, ip_address.c_str(), &(sa6.sin6_addr)) == 1;
    }

    static std::optional<std::string> get_hostname(const std::string& ip_address) {
        struct sockaddr_storage addr;
        socklen_t addr_len;

        // Try IPv4 first
        struct sockaddr_in* sin = reinterpret_cast<struct sockaddr_in*>(&addr);
        if (inet_pton(AF_INET, ip_address.c_str(), &(sin->sin_addr)) == 1) {
            sin->sin_family = AF_INET;
            addr_len = sizeof(struct sockaddr_in);
        } else {
            // Try IPv6
            struct sockaddr_in6* sin6 = reinterpret_cast<struct sockaddr_in6*>(&addr);
            if (inet_pton(AF_INET6, ip_address.c_str(), &(sin6->sin6_addr)) == 1) {
                sin6->sin6_family = AF_INET6;
                addr_len = sizeof(struct sockaddr_in6);
            } else {
                return std::nullopt; // invalid IP
            }
        }

        char host[NI_MAXHOST];
        int result = getnameinfo(reinterpret_cast<struct sockaddr*>(&addr), addr_len,
                                 host, sizeof(host), nullptr, 0, NI_NAMEREQD);
        if (result != 0) {
            return std::nullopt; // hostname not found
        }
        return std::string(host);
    }
};