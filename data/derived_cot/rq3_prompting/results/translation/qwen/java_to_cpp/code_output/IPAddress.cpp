#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

class IPAddress {
private:
    std::string ipAddress;

public:
    IPAddress(const std::string& ipAddress) : ipAddress(ipAddress) {}

    bool isValid() const {
        std::vector<std::string> octets;
        std::stringstream ss(ipAddress);
        std::string octet;
        while (std::getline(ss, octet, '.')) {
            octets.push_back(octet);
        }

        if (octets.size() != 4) {
            return false;
        }

        for (const auto& oct : octets) {
            try {
                int num = std::stoi(oct);
                if (num < 0 || num > 255) {
                    return false;
                }
            } catch (...) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> getOctets() const {
        std::vector<std::string> octets;
        if (isValid()) {
            std::stringstream ss(ipAddress);
            std::string octet;
            while (std::getline(ss, octet, '.')) {
                octets.push_back(octet);
            }
        }
        return octets;
    }

    std::string getBinary() const {
        if (!isValid()) {
            return "";
        }

        std::stringstream binaryString;
        std::stringstream ss(ipAddress);
        std::string octet;
        while (std::getline(ss, octet, '.')) {
            try {
                int num = std::stoi(octet);
                std::string bin = std::bitset<8>(num).to_string<char, std::char_traits<char>, std::allocator<char>>();
                long long value = 0;
                for (char c : bin) {
                    value = value * 10 + (c - '0');
                }
                char buffer[9];
                snprintf(buffer, sizeof(buffer), "%08lld", value);
                binaryString << buffer << '.';
            } catch (...) {
                return "";
            }
        }

        std::string result = binaryString.str();
        if (!result.empty()) {
            result.pop_back();
        }
        return result;
    }
};