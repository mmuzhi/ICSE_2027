#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <bitset>
#include <algorithm>

class IPAddress {
private:
    std::string ipAddress;

public:
    IPAddress(const std::string& ipAddress) : ipAddress(ipAddress) {}

    bool is_valid() const {
        std::istringstream iss(ipAddress);
        std::string octet;
        std::vector<std::string> octets;
        while (std::getline(iss, octet, '.')) {
            octets.push_back(octet);
        }

        if (octets.size() != 4) {
            return false;
        }

        for (const auto& oct : octets) {
            try {
                int num = std::stoi(oct);
                if (num < 0 || num > 255) {
                    return false;
                }
            } catch (const std::invalid_argument& | const std::out_of_range&) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> getOctets() const {
        std::vector<std::string> octets;
        if (isValid()) {
            std::istringstream iss(ipAddress);
            std::string octet;
            while (std::getline(iss, octet, '.')) {
                octets.push_back(octet);
            }
        }
        return octets;
    }

    std::string get_binary() const {
        if (!isValid()) {
            return "";
        }

        std::istringstream iss(ipAddress);
        std::string octet;
        std::vector<std::string> octets;
        while (std::getline(iss, octet, '.')) {
            octets.push_back(octet);
        }

        std::string binaryString;
        for (size_t i = 0; i < octets.size(); ++i) {
            int num = std::stoi(octets[i]);
            std::bitset<8> bs(num);
            std::string binaryOctet = bs.to_string();
            binaryString += binaryOctet;
            if (i != octets.size() - 1) {
                binaryString += ".";
            }
        }
        return binaryString;
    }
};