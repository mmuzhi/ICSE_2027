#include <string>
#include <sstream>
#include <bitset>

class NumberConverter {
public:
    static std::string decimalToBinary(int decimalNum) {
        if (decimalNum == 0) return "0";
        unsigned u = static_cast<unsigned>(decimalNum);
        std::string bits = std::bitset<32>(u).to_string();
        return bits.substr(bits.find('1'));
    }

    static int binaryToDecimal(const std::string& binaryNum) {
        return std::stoi(binaryNum, nullptr, 2);
    }

    static std::string decimalToOctal(int decimalNum) {
        std::ostringstream ss;
        ss << std::oct << static_cast<unsigned>(decimalNum);
        return ss.str();
    }

    static int octalToDecimal(const std::string& octalNum) {
        return std::stoi(octalNum, nullptr, 8);
    }

    static std::string decimalToHex(int decimalNum) {
        std::ostringstream ss;
        ss << std::hex << static_cast<unsigned>(decimalNum);
        return ss.str();
    }

    static int hexToDecimal(const std::string& hexNum) {
        return std::stoi(hexNum, nullptr, 16);
    }
};