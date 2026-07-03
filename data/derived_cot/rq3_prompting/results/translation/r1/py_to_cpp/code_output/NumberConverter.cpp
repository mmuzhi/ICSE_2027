#include <string>
#include <sstream>
#include <algorithm>

class NumberConverter {
public:
    static std::string decimal_to_binary(int decimal_num) {
        if (decimal_num == 0) return "0";
        std::string bin;
        bool negative = decimal_num < 0;
        unsigned int num = negative ? -decimal_num : decimal_num;
        while (num > 0) {
            bin = (num & 1 ? "1" : "0") + bin;
            num >>= 1;
        }
        if (negative) {
            return "b" + bin;
        }
        return bin;
    }

    static int binary_to_decimal(const std::string& binary_num) {
        return std::stoi(binary_num, nullptr, 2);
    }

    static std::string decimal_to_octal(int decimal_num) {
        if (decimal_num == 0) return "0";
        bool negative = decimal_num < 0;
        unsigned int num = negative ? -decimal_num : decimal_num;
        std::ostringstream oss;
        oss << std::oct << num;
        std::string oct_str = oss.str();
        if (negative) {
            return "o" + oct_str;
        }
        return oct_str;
    }

    static int octal_to_decimal(const std::string& octal_num) {
        return std::stoi(octal_num, nullptr, 8);
    }

    static std::string decimal_to_hex(int decimal_num) {
        if (decimal_num == 0) return "0";
        bool negative = decimal_num < 0;
        unsigned int num = negative ? -decimal_num : decimal_num;
        std::ostringstream oss;
        oss << std::hex << num;
        std::string hex_str = oss.str();
        if (negative) {
            return "x" + hex_str;
        }
        return hex_str;
    }

    static int hex_to_decimal(const std::string& hex_num) {
        return std::stoi(hex_num, nullptr, 16);
    }
};