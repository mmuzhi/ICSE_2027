#include <string>
#include <optional>
#include <stdexcept>
#include <arpa/inet.h>
#include <netdb.h>

class IpUtil {
public:
    static bool is_valid_ipv4(const std::string& ip_address) {
        struct in_addr addr;
        // inet_pton returns 1 on success, 0 if the address is not valid, -1 on error
        return inet_pton(AF_INET, ip_address.c_str(), &addr) == 1;
    }

    static bool is_valid_ipv6(const std::string& ip_address) {
        struct in6_addr addr;
        return inet_pton(AF_INET6, ip_address.c_str(), &addr) == 1;
    }

    static std::optional<std::string> get_hostname(const std::string& ip_address) {
        struct addrinfo hints = {};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        struct addrinfo* res = nullptr;
        
        // getaddrinfo handles both IPv4 and IPv6 addresses and resolves them.
        // If the address is invalid, it throws an equivalent of socket.gaierror
        int err = getaddrinfo(ip_address.c_str(), nullptr, &hints, &res);
        if (err != 0) {
            throw std::runtime_error(gai_strerror(err));
        }
        
        char host[NI_MAXHOST];
        // NI_NAMEREQD ensures we only get the hostname, returning an error if only an IP is available.
        // This corresponds to catching socket.herror in Python.
        int status = getnameinfo(res->ai_addr, res->ai_addrlen, host, sizeof(host), nullptr, 0, NI_NAMEREQD);
        freeaddrinfo(res);
        
        if (status != 0) {
            return std::nullopt; // Equivalent to returning None
        }
        
        return std::string(host);
    }
};