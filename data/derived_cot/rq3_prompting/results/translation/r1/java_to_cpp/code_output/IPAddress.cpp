#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include <stdexcept>

class IPAddress {
private:
    std::string ipAddress;

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
    IPAddress(const std::string& ipAddress) : ipAddress(ipAddress) {}

    bool isValid() const {
        std::vector<std::string> octets = split(ipAddress, '.');
        if (octets.size() != 4) {
            return false;
        }
        for (const std::string& octet : octets) {
            try {
                int num = std::stoi(octet);
                if (num < 0 || num > 255) {
                    return false;
                }
            } catch (const std::invalid_argument&) {
                return false;
            } catch (const std::out_of_range&) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> getOctets() const {
        std::vector<std::string> octetsList;
        if (isValid()) {
            octetsList = split(ipAddress, '.');
        }
        return octetsList;
    }

    std::string getBinary() const {
        if (!isValid()) {
            return "";
        }
        std::string binaryString;
        std::vector<std::string> octets = split(ipAddress, '.');
        for (const std::string& octet : octets) {
            int num = std::stoi(octet);
            std::string bin = std::bitset<8>(num).to_string();
            binaryString += bin + ".";
        }
        if (!binaryString.empty()) {
            binaryString.pop_back(); // remove trailing '.'
        }
        return binaryString;
    }
};