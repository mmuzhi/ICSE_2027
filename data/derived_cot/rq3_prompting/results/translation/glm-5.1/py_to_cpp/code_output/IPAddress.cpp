#include <string>
#include <vector>
#include <bitset>

class IPAddress {
private:
    std::string ip_address;

    static bool is_digit_string(const std::string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (c < '0' || c > '9') return false;
        }
        return true;
    }

    static std::vector<std::string> split_by_dot(const std::string& s) {
        std::vector<std::string> result;
        size_t start = 0;
        size_t pos = s.find('.');
        while (pos != std::string::npos) {
            result.push_back(s.substr(start, pos - start));
            start = pos + 1;
            pos = s.find('.', start);
        }
        result.push_back(s.substr(start));
        return result;
    }

public:
    IPAddress(const std::string& ip_address) : ip_address(ip_address) {}

    bool is_valid() {
        std::vector<std::string> octets = split_by_dot(ip_address);
        if (octets.size() != 4) return false;
        for (const auto& octet : octets) {
            if (!is_digit_string(octet)) return false;
            int val = std::stoi(octet);
            if (val < 0 || val > 255) return false;
        }
        return true;
    }

    std::vector<std::string> get_octets() {
        if (is_valid()) {
            return split_by_dot(ip_address);
        } else {
            return {};
        }
    }

    std::string get_binary() {
        if (is_valid()) {
            std::vector<std::string> binary_octets;
            for (const auto& octet : get_octets()) {
                binary_octets.push_back(std::bitset<8>(std::stoi(octet)).to_string());
            }
            std::string result;
            for (size_t i = 0; i < binary_octets.size(); i++) {
                if (i > 0) result += '.';
                result += binary_octets[i];
            }
            return result;
        } else {
            return "";
        }
    }
};