#include <string>
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>

namespace org {
namespace example {

class IpUtil {

public:
    static bool isValidIpv4(const std::string& ipAddress) {
        if (ipAddress.find('.') == std::string::npos || ipAddress.find(':') != std::string::npos) {
            return false;
        }

        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;

        int status = getaddrinfo(ipAddress.c_str(), NULL, &hints, &res);
        if (status != 0) {
            return false;
        }

        freeaddrinfo(res);
        return true;
    }

    static bool isValidIpv6(const std::string& ipAddress) {
        if (ipAddress.find(':') == std::string::npos) {
            return false;
        }

        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET6;

        int status = getaddrinfo(ipAddress.c_str(), NULL, &hints, &res);
        if (status != 0) {
            return false;
        }

        freeaddrinfo(res);
        return true;
    }

    static std::string getHostname(const std::string& ipAddress) {
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;

        int status = getaddrinfo(ipAddress.c_str(), NULL, &hints, &res);
        if (status != 0) {
            return nullptr;
        }

        if (ipAddress == "0.0.0.0") {
            freeaddrinfo(res);
            struct addrinfo hints_local, *res_local;
            memset(&hints_local, 0, sizeof(hints_local));
            hints_local.ai_family = AF_UNSPEC;

            int status_local = getaddrinfo("localhost", NULL, &hints_local, &res_local);
            if (status_local != 0) {
                return nullptr;
            }

            char host[NI_MAXHOST];
            if (getnameinfo(res_local->ai_addr, res_local->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NAMEREQD) == 0) {
                std::string hostname(host);
                freeaddrinfo(res_local);
                return hostname;
            }
            freeaddrinfo(res_local);
            return nullptr;
        }

        char host[NI_MAXHOST];
        if (getnameinfo(res->ai_addr, res->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NAMEREQD) == 0) {
            std::string hostname(host);
            if (hostname == ipAddress) {
                freeaddrinfo(res);
                return nullptr;
            }
            freeaddrinfo(res);
            return hostname;
        }

        freeaddrinfo(res);
        return nullptr;
    }
};

} // namespace example
} // namespace org