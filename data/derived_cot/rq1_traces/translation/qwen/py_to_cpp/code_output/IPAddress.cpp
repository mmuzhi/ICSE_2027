#include <string>
#include <vector>
#include <sstream>
#include <cctype>

class IPAddress {
private:
    std::string ip_address;
    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream iss(s);
        while (std::getline(iss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    IPAddress(const std::string& ip_address) : ip_address(ip_address) {}

    bool is_valid() {
        std::vector<std::string> parts = split(ip_address, '.');
        if (parts.size() != 4) {
            return false;
        }
        for (const auto& part : parts) {
            if (part.empty()) {
                return false;
            }
            for (char c : part) {
                if (!std::isdigit(c)) {
                    return false;
                }
            }
            int num = std::stoi(part);
            if (num < 0 || num > 255) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_octets() {
        if (is_valid()) {
            return split(ip_address, '.');
        } else {
            return {};
        }
    }

    std::string get_binary() {
        if (!is_valid()) {
            return "";
        }
        std::vector<std::string> octets = get_octets();
        std::string result;
        for (size_t i = 0; i < octets.size(); i++) {
            if (i > 0) {
                result += '.';
            }
            int num = std::stoi(octets[i]);
            std::string bin = "";
            for (int j = 7; j >= 0; j--) {
                bin += (num & (1 << j)) ? '1' : '0';
            }
            result += bin;
        }
        return result;
    }
};