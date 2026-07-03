#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <stdexcept>

class IPAddress {
private:
    std::string ipAddress;

    static std::vector<std::string> splitByDot(const std::string& s) {
        std::vector<std::string> result;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, '.')) {
            result.push_back(token);
        }
        // Java's split discards trailing empty strings
        while (!result.empty() && result.back().empty()) {
            result.pop_back();
        }
        return result;
    }

    static bool isAllDigits(const std::string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) return false;
        }
        return true;
    }

public:
    IPAddress(const std::string& ipAddress) : ipAddress(ipAddress) {}

    bool isValid() const {
        std::vector<std::string> octets = splitByDot(ipAddress);
        if (octets.size() != 4) {
            return false;
        }
        for (const std::string& octet : octets) {
            if (!isAllDigits(octet)) {
                return false;
            }
            try {
                int num = std::stoi(octet);
                if (num < 0 || num > 255) {
                    return false;
                }
            } catch (const std::exception&) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> getOctets() const {
        std::vector<std::string> octetsList;
        if (isValid()) {
            std::vector<std::string> octets = splitByDot(ipAddress);
            for (const std::string& octet : octets) {
                octetsList.push_back(octet);
            }
        }
        return octetsList;
    }

    std::string getBinary() const {
        if (isValid()) {
            std::string binaryString;
            std::vector<std::string> octets = splitByDot(ipAddress);
            for (const std::string& octet : octets) {
                int num = std::stoi(octet);
                std::string binaryOctet;
                for (int i = 7; i >= 0; --i) {
                    binaryOctet += ((num >> i) & 1) ? '1' : '0';
                }
                binaryString += binaryOctet + ".";
            }
            return binaryString.substr(0, binaryString.size() - 1);
        }
        return "";
    }
};