#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <stdexcept>

class IPAddress {
private:
    std::string ipAddress;

    // Helper to perfectly mimic Java's split("\\.") which discards trailing empty strings
    std::vector<std::string> splitByDot(const std::string& str) const {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, '.')) {
            tokens.push_back(token);
        }
        // Java's split discards trailing empty strings if there was at least one match
        if (str.find('.') != std::string::npos) {
            while (!tokens.empty() && tokens.back().empty()) {
                tokens.pop_back();
            }
        }
        return tokens;
    }

    // Helper to perfectly mimic Java's Integer.parseInt() behavior
    int parseInt(const std::string& s) const {
        if (s.empty()) {
            throw std::invalid_argument("empty string");
        }
        size_t start = 0;
        if (s[0] == '+' || s[0] == '-') {
            start = 1;
        }
        if (start == s.length()) {
            throw std::invalid_argument("only sign");
        }
        for (size_t i = start; i < s.length(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(s[i]))) {
                throw std::invalid_argument("invalid character");
            }
        }
        try {
            long long val = std::stoll(s);
            if (val > 2147483647 || val < -2147483648) {
                throw std::out_of_range("out of int range");
            }
            return static_cast<int>(val);
        } catch (const std::out_of_range&) {
            throw;
        } catch (const std::invalid_argument&) {
            throw;
        }
    }

public:
    IPAddress(const std::string& ipAddress) : ipAddress(ipAddress) {}

    bool isValid() const {
        std::vector<std::string> octets = splitByDot(ipAddress);
        if (octets.size() != 4) {
            return false;
        }
        for (const std::string& octet : octets) {
            try {
                int num = parseInt(octet);
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
                int num = parseInt(octet);
                std::string binStr;
                // Equivalent to String.format("%08d", Integer.parseInt(Integer.toBinaryString(num)))
                for (int i = 7; i >= 0; --i) {
                    binStr += ((num >> i) & 1) ? '1' : '0';
                }
                binaryString += binStr + ".";
            }
            return binaryString.substr(0, binaryString.length() - 1);
        }
        return "";
    }
};