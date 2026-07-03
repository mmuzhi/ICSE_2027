#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>

class IPAddress {
private:
    std::string ip_address;
    std::vector<std::string> octets;

    void split_ip() {
        std::stringstream ss(ip_address);
        std::string part;
        while (std::getline(ss, part, '.')) {
            octets.push_back(part);
        }
    }

public:
    IPAddress(const std::string& ip_address) : ip_address(ip_address) {
        split_ip();
    }

    bool is_valid() {
        if (octets.size() != 4) {
            return false;
        }
        for (const auto& octet : octets) {
            if (octet.empty()) {
                return false;
            }
            for (char c : octet) {
                if (!std::isdigit(c)) {
                    return false;
                }
            }
            try {
                int num = std::stoi(octet);
                if (num < 0 || num > 255) {
                    return false;
                }
            } catch (...) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_octets() {
        if (is_valid()) {
            return octets;
        }
        return std::vector<std::string>();
    }

    std::string get_binary() {
        if (is_valid()) {
            std::vector<std::string> binary_octets;
            for (const auto& octet : octets) {
                int num = std::stoi(octet);
                std::string binary = "";
                for (int i = 7; i >= 0; i--) {
                    binary += ((num >> i) & 1) ? '1' : '0';
                }
                binary_octets.push_back(binary);
            }
            return join_strings(binary_octets, ".");
        }
        return "";
    }

    static std::string join_strings(const std::vector<std::string>& parts, const std::string& delimiter) {
        if (parts.empty()) {
            return "";
        }
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); i++) {
            result += delimiter + parts[i];
        }
        return result;
    }
};