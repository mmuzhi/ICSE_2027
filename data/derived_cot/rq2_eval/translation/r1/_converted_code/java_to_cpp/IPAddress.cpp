#include <vector>
#include <string>
#include <sstream>
#include <bitset>
#include <stdexcept>

class IPAddress {
private:
    std::string ipAddress;

    std::vector<std::string> split(const std::string& s, char delimiter) const {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

public:
    IPAddress(const std::string& ipAddr) : ipAddress(ipAddr) {}

    bool is_valid() const {
        std::vector<std::string> octets = split(ipAddress, '.');
        if (octets.size() != 4) {
            return false;
        }
        for (const auto& octet : octets) {
            if (octet.empty()) {
                return false;
            }
            try {
                size_t pos;
                int num = std::stoi(octet, &pos, 10);
                if (pos != octet.size()) {
                    return false;
                }
                if (num < 0 || num > 255) {
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

    std::vector<std::string> getOctets() const {
        if (isValid()) {
            return split(ipAddress, '.');
        }
        return std::vector<std::string>();
    }

    std::string get_binary() const {
        if (isValid()) {
            std::vector<std::string> octets = split(ipAddress, '.');
            std::string binaryString;
            for (const auto& octet : octets) {
                int num = std::stoi(octet);
                std::bitset<8> bits(num);
                binaryString += bits.to_string() + ".";
            }
            if (!binaryString.empty()) {
                binaryString.pop_back();
            }
            return binaryString;
        }
        return "";
    }
};