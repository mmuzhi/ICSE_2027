#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <bitset>

class IPAddress {
private:
    std::string ip_address;

    bool isValidInternal() const {
        // Split by '.'
        std::vector<std::string> octets;
        std::istringstream stream(ip_address);
        std::string token;
        while (std::getline(stream, token, '.')) {
            octets.push_back(token);
        }
        if (octets.size() != 4) return false;
        for (const auto& oct : octets) {
            if (oct.empty()) return false;
            // Check all characters are digits
            for (char c : oct) {
                if (!std::isdigit(static_cast<unsigned char>(c))) return false;
            }
            // Convert to int and check range
            int val = std::stoi(oct);
            if (val < 0 || val > 255) return false;
        }
        return true;
    }

public:
    IPAddress(const std::string& ip) : ip_address(ip) {}

    bool is_valid() const {
        return isValidInternal();
    }

    std::vector<std::string> get_octets() const {
        if (!is_valid()) return {};
        std::vector<std::string> octets;
        std::istringstream stream(ip_address);
        std::string token;
        while (std::getline(stream, token, '.')) {
            octets.push_back(token);
        }
        return octets;
    }

    std::string get_binary() const {
        if (!is_valid()) return "";
        std::vector<std::string> octets = get_octets();
        std::vector<std::string> binary_octets;
        for (const auto& oct : octets) {
            int val = std::stoi(oct);
            // Format to 8-bit binary with leading zeros
            std::bitset<8> bits(val);
            binary_octets.push_back(bits.to_string());
        }
        // Join with '.'
        std::string result;
        for (size_t i = 0; i < binary_octets.size(); ++i) {
            if (i > 0) result += ".";
            result += binary_octets[i];
        }
        return result;
    }
};