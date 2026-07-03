#include <string>
#include <optional>
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
#else
    #include <sys/socket.h>
    #include <netdb.h>
    #include <arpa/inet.h>
#endif

class IpUtil {
private:
#ifdef _WIN32
    static void ensure_winsock_init() {
        static bool initialized = false;
        if (!initialized) {
            WSADATA wsaData;
            WSAStartup(MAKEWORD(2, 2), &wsaData);
            initialized = true;
        }
    }
#else
    static void ensure_winsock_init() {}
#endif

public:
    static bool is_valid_ipv4(const std::string& ip_address) {
        ensure_winsock_init();
        struct in_addr addr;
        return (inet_pton(AF_INET, ip_address.c_str(), &addr) == 1);
    }

    static bool is_valid_ipv6(const std::string& ip_address) {
        ensure_winsock_init();
        struct in6_addr addr;
        return (inet_pton(AF_INET6, ip_address.c_str(), &addr) == 1);
    }

    static std::optional<std::string> get_hostname(const std::string& ip_address) {
        ensure_winsock_init();
        struct in_addr addr4;
        struct in6_addr addr6;
        int family;
        const void *addr_ptr;
        socklen_t addr_len;

        if (is_valid_ipv4(ip_address)) {
            if (inet_pton(AF_INET, ip_address.c_str(), &addr4) != 1) {
                return std::nullopt;
            }
            family = AF_INET;
            addr_ptr = &addr4;
            addr_len = sizeof(addr4);
        }
        else if (is_valid_ipv6(ip_address)) {
            if (inet_pton(AF_INET6, ip_address.c_str(), &addr6) != 1) {
                return std::nullopt;
            }
            family = AF_INET6;
            addr_ptr = &addr6;
            addr_len = sizeof(addr6);
        }
        else {
            return std::nullopt;
        }

#ifdef _WIN32
        const char *addr_ptr_cast = static_cast<const char*>(addr_ptr);
        int len = static_cast<int>(addr_len);
#else
        const void *addr_ptr_cast = addr_ptr;
        socklen_t len = addr_len;
#endif

        struct hostent *he = gethostbyaddr(addr_ptr_cast, len, family);
        if (he == nullptr) {
            return std::nullopt;
        }
        return std::string(he->h_name);
    }
};