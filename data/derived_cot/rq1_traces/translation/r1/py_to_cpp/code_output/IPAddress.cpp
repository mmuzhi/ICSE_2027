#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <bitset>

class IPAddress {
private:
    std::string ip_address;

    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    IPAddress(std::string ip_address) : ip_address(ip_address) {}

    bool is_valid() const {
        std::vector<std::string> tokens = split(ip_address, '.');
        if (tokens.size() != 4) {
            return false;
        }
        for (const std::string& token : tokens) {
            if (token.empty()) {
                return false;
            }
            for (char c : token) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    return false;
                }
            }
            try {
                size_t pos;
                unsigned long value = std::stoul(token, &pos);
                if (value > 255) {
                    return false;
                }
            } catch (const std::invalid_argument& e) {
                return false;
            } catch (const std::out_of_range& e) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_octets() const {
        if (is_valid()) {
            return split(ip_address, '.');
        } else {
            return std::vector<std::string>();
        }
    }

    std::string get_binary() const {
        if (!is_valid()) {
            return "";
        }
        std::vector<std::string> octets = get_octets();
        std::vector<std::string> binary_octets;
        for (const auto& octet : octets) {
            int value = std::stoi(octet);
            binary_octets.push_back(std::bitset<8>(value).to_string());
        }
        std::string result;
        for (size_t i = 0; i < binary_octets.size(); ++i) {
            if (i != 0) {
                result += '.';
            }
            result += binary_octets[i];
        }
        return result;
    }
};