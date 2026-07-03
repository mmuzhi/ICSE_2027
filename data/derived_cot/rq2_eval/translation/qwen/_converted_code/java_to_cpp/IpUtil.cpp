#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>

bool isValidIpv4(const std::string& ipAddress) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;

    int status = getaddrinfo(ipAddress.c_str(), NULL, &hints, &res);
    if (status != 0) {
        return false;
    }

    freeaddrinfo(res);
    return true;
}

bool isValidIpv6(const std::string& ipAddress) {
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;

    int status = getaddrinfo(ipAddress.c_str(), NULL, &res);
    if (status != 0) {
        return false;
    }

    freeaddrinfo(res);
    return true;
}

std::string getHostname(const std::string& ipAddress) {
    try {
        if (ipAddress == "0.0.0.0") {
            struct addrinfo hintsLocal, *resLocal;
            memset(&hintsLocal, 0, sizeof hintsLocal);
            hintsLocal.ai_family = AF_UNSPEC;

            int statusLocal = getaddrinfo(NULL, NULL, &hintsLocal, &resLocal);
            if (statusLocal != 0) {
                return "";
            }

            char hostbuffer[NI_MAXHOST];
            char *hostname = NULL;
            if (getnameinfo(resLocal->ai_addr, resLocal->ai_addrlen, hostbuffer, sizeof(hostbuffer), NULL, 0, NI_NAMEREQD) == 0) {
                hostname = strdup(hostbuffer);
            }

            freeaddrinfo(resLocal);
            if (hostname == NULL) {
                return "";
            }

            std::string result = hostname;
            free(hostname);
            return result;
        }

        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;

        int status = getaddrinfo(ipAddress.c_str(), NULL, &hints, &res);
        if (status != 0) {
            return "";
        }

        char hostbuffer[NI_MAXHOST];
        char servbuffer[NI_MAXSERV];
        if (getnameinfo(res->ai_addr, res->ai_addrlen, hostbuffer, sizeof(hostbuffer), servbuffer, sizeof(servbuffer), NI_NAMEREQD) != 0) {
            freeaddrinfo(res);
            return "";
        }

        char *hostname = strdup(hostbuffer);
        freeaddrinfo(res);

        if (hostname == NULL) {
            return "";
        }

        if (std::string(hostname) == ipAddress) {
            free(hostname);
            return "";
        }

        std::string result = hostname;
        free(hostname);
        return result;
    } catch (...) {
        return "";
    }
}