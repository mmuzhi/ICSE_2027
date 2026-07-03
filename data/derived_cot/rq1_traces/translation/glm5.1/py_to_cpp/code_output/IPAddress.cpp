#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <cctype>

class IPAddress {
private:
    std::string ip_address;

    std::vector<std::string> split_ip() const {
        std::vector<std::string> octets;
        std::stringstream ss(ip_address);
        std::string token;
        while (std::getline(ss, token, '.')) {
            octets.push_back(token);
        }
        return octets;
    }

public:
    IPAddress(std::string ip_address) : ip_address(std::move(ip_address)) {}

    bool is_valid() const {
        std::vector<std::string> octets = split_ip();
        if (octets.size() != 4) {
            return false;
        }
        for (const std::string& octet : octets) {
            if (octet.empty()) return false;
            for (char c : octet) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    return false;
                }
            }
            
            // Parse the value manually to avoid std::stoi overflow exceptions 
            // and perfectly match Python's arbitrary precision int() behavior.
            long long val = 0;
            for (char c : octet) {
                val = val * 10 + (c - '0');
                if (val > 255) {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<std::string> get_octets() const {
        if (is_valid()) {
            return split_ip();
        } else {
            return {};
        }
    }

    std::string get_binary() const {
        if (is_valid()) {
            std::vector<std::string> octets = get_octets();
            std::string result;
            for (size_t i = 0; i < octets.size(); ++i) {
                if (i > 0) {
                    result += ".";
                }
                
                long long val = 0;
                for (char c : octets[i]) {
                    val = val * 10 + (c - '0');
                }
                
                // Format as 8-bit binary padded with zeros
                result += std::bitset<8>(static_cast<unsigned long long>(val)).to_string();
            }
            return result;
        } else {
            return "";
        }
    }
};