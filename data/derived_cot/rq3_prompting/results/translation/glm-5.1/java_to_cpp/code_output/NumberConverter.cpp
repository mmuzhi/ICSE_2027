#include <string>
#include <bitset>
#include <sstream>

class NumberConverter {
public:
    static std::string decimalToBinary(int decimalNum) {
        std::string bits = std::bitset<32>(static_cast<unsigned int>(decimalNum)).to_string();
        size_t firstOne = bits.find('1');
        if (firstOne == std::string::npos) return "0";
        return bits.substr(firstOne);
    }

    static int binaryToDecimal(const std::string& binaryNum) {
        return std::stoi(binaryNum, nullptr, 2);
    }

    static std::string decimalToOctal(int decimalNum) {
        std::ostringstream oss;
        oss << std::oct << static_cast<unsigned int>(decimalNum);
        return oss.str();
    }

    static int octalToDecimal(const std::string& octalNum) {
        return std::stoi(octalNum, nullptr, 8);
    }

    static std::string decimalToHex(int decimalNum) {
        std::ostringstream oss;
        oss << std::hex << static_cast<unsigned int>(decimalNum);
        return oss.str();
    }

    static int hexToDecimal(const std::string& hexNum) {
        return std::stoi(hexNum, nullptr, 16);
    }
};