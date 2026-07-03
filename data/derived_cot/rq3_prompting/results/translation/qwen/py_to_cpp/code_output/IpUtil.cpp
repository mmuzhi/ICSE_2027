#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <memory>

class IpUtil {
public:
    static bool is_valid_ipv4(const std::string& ip_address) {
        struct sockaddr_in sa;
        if (::inet_pton(AF_INET, ip_address.c_str(), &(sa.sin_addr)) == 1) {
            return true;
        }
        return false;
    }

    static bool is_valid_ipv6(const std::string& ip_address) {
        struct sockaddr_in6 sa;
        if (::inet_pton(AF_INET6, ip_address.c_str(), &(sa.sin6_addr)) == 1) {
            return true;
        }
        return false;
    }

    static std::string* get_hostname(const std::string& ip_address) {
        struct hostent* host = ::gethostbyaddr(
            (const char*)ip_address.c_str(),
            ip_address.size(),
            AF_INET
        );
        if (host != nullptr) {
            return std::strdup(host->h_name);
        }
        return nullptr;
    }
};