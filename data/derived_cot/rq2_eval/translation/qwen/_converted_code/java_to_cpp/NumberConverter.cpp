#include <string>
#include <algorithm>
#include <cstdlib>

class NumberConverter {
public:
    static std::string decimal_to_binary(int decimalNum) {
        if (decimalNum == 0) {
            return "0";
        }
        std::string result;
        unsigned int value = static_cast<unsigned int>(decimalNum);
        while (value) {
            result.push_back('0' + (value & 1));
            value >>= 1;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    static int binary_to_decimal(const std::string& binaryNum) {
        return std::stoi(binaryNum, nullptr, 2);
    }

    static std::string decimal_to_octal(int decimalNum) {
        if (decimalNum == 0) {
            return "0";
        }
        std::string result;
        unsigned int value = static_cast<unsigned int>(decimalNum);
        while (value) {
            result.push_back('0' + (value % 8));
            value /= 8;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    static int octal_to_decimal(const std::string& octalNum) {
        return std::stoi(octalNum, nullptr, 8);
    }

    static std::string decimal_to_hex(int decimalNum) {
        if (decimalNum == 0) {
            return "0";
        }
        std::string result;
        unsigned int value = static_cast<unsigned int>(decimalNum);
        while (value) {
            int remainder = value % 16;
            if (remainder < 10) {
                result.push_back('0' + remainder);
            } else {
                result.push_back('A' + (remainder - 10));
            }
            value /= 16;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    static int hex_to_decimal(const std::string& hexNum) {
        return std::stoi(hexNum, nullptr, 16);
    }
};