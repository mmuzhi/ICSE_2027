#include <bitset>
#include <string>
#include <cstdlib>
#include <iostream>

namespace NumberConverter {

static std::string decimalToBinary(int decimalNum) {
    if (decimalNum == 0) {
        return "0";
    }
    bool isNegative = decimalNum < 0;
    unsigned int num = static_cast<unsigned int>(isNegative ? -decimalNum : decimalNum);
    unsigned int inverted = ~num;
    inverted = inverted + 1;
    std::bitset<32> bits(inverted);
    std::string s = bits.to_string();
    size_t firstNonZero = s.find('1');
    if (firstNonZero == std::string::npos) {
        return "0";
    }
    return s.substr(firstNonZero);
}

static int binaryToDecimal(const std::string& binaryNum) {
    return std::stoi(binaryNum, nullptr, 2);
}

static std::string decimalToOctal(int decimalNum) {
    if (decimalNum == 0) {
        return "0";
    }
    bool isNegative = decimalNum < 0;
    unsigned int num = static_cast<unsigned int>(isNegative ? -decimalNum : decimalNum);
    unsigned int inverted = ~num;
    inverted = inverted + 1;
    std::bitset<32> bits(inverted);
    std::string binary = bits.to_string();
    size_t firstNonZero = binary.find('1');
    if (firstNonZero == std::string::npos) {
        return "0";
    }
    binary = binary.substr(firstNonZero);
    std::string octal;
    for (size_t i = 0; i < binary.size(); i += 3) {
        std::string chunk = binary.substr(i, 3);
        while (chunk.length() < 3) {
            chunk = '0' + chunk;
        }
        int digit = std::stoi(chunk, nullptr, 2);
        octal += ('0' + digit);
    }
    return octal;
}

static int octalToDecimal(const std::string& octalNum) {
    return std::stoi(octalNum, nullptr, 8);
}

static std::string decimalToHex(int decimalNum) {
    if (decimalNum == 0) {
        return "0";
    }
    bool isNegative = decimalNum < 0;
    unsigned int num = static_cast<unsigned int>(isNegative ? -decimalNum : decimalNum);
    unsigned int inverted = ~num;
    inverted = inverted + 1;
    std::bitset<32> bits(inverted);
    std::string binary = bits.to_string();
    size_t firstNonZero = binary.find('1');
    if (firstNonZero == std::string::npos) {
        return "0";
    }
    binary = binary.substr(firstNonZero);
    std::string hex;
    for (size_t i = 0; i < binary.size(); i += 4) {
        std::string chunk = binary.substr(i, 4);
        while (chunk.length() < 4) {
            chunk = '0' + chunk;
        }
        int digit = std::stoi(chunk, nullptr, 2);
        if (digit < 10) {
            hex += ('0' + digit);
        } else {
            hex += ('A' + (digit - 10));
        }
    }
    return hex;
}

static int hexToDecimal(const std::string& hexNum) {
    return std::stoi(hexNum, nullptr, 16);
}
}