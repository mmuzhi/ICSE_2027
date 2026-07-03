#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <string>
#include <optional>
#include <unistd.h>

namespace org_example {

    static bool resolveHost(const std::string& host) {
        struct addrinfo hints, *res = nullptr;
        std::memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        int err = getaddrinfo(host.c_str(), nullptr, &hints, &res);
        if (err) {
            return false;
        }
        freeaddrinfo(res);
        return true;
    }

    bool isValidIpv4(const std::string& ipAddress) {
        if (ipAddress.find('.') == std::string::npos || ipAddress.find(':') != std::string::npos) {
            return false;
        }
        return resolveHost(ipAddress);
    }

    bool isValidIpv6(const std::string& ipAddress) {
        if (ipAddress.find(':') == std::string::npos) {
            return false;
        }
        return resolveHost(ipAddress);
    }

    std::optional<std::string> getHostname(const std::string& ipAddress) {
        if (ipAddress == "0.0.0.0") {
            char hostnameBuf[1024];
            if (gethostname(hostnameBuf, sizeof(hostnameBuf)) != 0) {
                return std::nullopt;
            }
            return std::string(hostnameBuf);
        } else {
            struct addrinfo hints, *res = nullptr;
            std::memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC;
            hints.ai_flags = AI_CANONNAME;

            int err = getaddrinfo(ipAddress.c_str(), nullptr, &hints, &res);
            if (err != 0) {
                return std::nullopt;
            }
            std::string canonical = res->ai_canonname;
            if (canonical == ipAddress) {
                freeaddrinfo(res);
                return std::nullopt;
            }
            freeaddrinfo(res);
            return canonical;
        }
    }

} // namespace org_example