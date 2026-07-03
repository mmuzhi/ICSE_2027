#include <string>
#include <algorithm>
#include <stdexcept>

class NumberConverter {
public:
    static std::string decimal_to_binary(int decimal_num) {
        if (decimal_num == 0) return "0";
        if (decimal_num < 0) {
            return "-" + decimal_to_binary(-decimal_num);
        }
        std::string binary;
        while (decimal_num) {
            binary.push_back('0' + (decimal_num & 1));
            decimal_num >>= 1;
        }
        std::reverse(binary.begin(), binary.end());
        return binary;
    }

    static int binary_to_decimal(std::string binary_num) {
        if (binary_num.empty()) {
            throw std::invalid_argument("Empty string");
        }
        if (binary_num[0] == '-') {
            return -binary_to_decimal(binary_num.substr(1));
        }
        int decimal_num = 0;
        for (char c : binary_num) {
            if (c == '0' || c == '1') {
                decimal_num = decimal_num * 2 + (c - '0');
            } else {
                throw std::invalid_argument("Invalid binary digit");
            }
        }
        return decimal_num;
    }

    static std::string decimal_to_octal(int decimal_num) {
        if (decimal_num == 0) return "0";
        if (decimal_num < 0) {
            return "-" + decimal_to_octal(-decimal_num);
        }
        std::string octal;
        while (decimal_num) {
            octal.push_back('0' + (decimal_num % 8));
            decimal_num /= 8;
        }
        std::reverse(octal.begin(), octal.end());
        return octal;
    }

    static int octal_to_decimal(std::string octal_num) {
        if (octal_num.empty()) {
            throw std::invalid_argument("Empty string");
        }
        if (octal_num[0] == '-') {
            return -octal_to_decimal(octal_num.substr(1));
        }
        int decimal_num = 0;
        for (char c : octal_num) {
            if (c >= '0' && c <= '7') {
                decimal_num = decimal_num * 8 + (c - '0');
            } else {
                throw std::invalid_argument("Invalid octal digit");
            }
        }
        return decimal_num;
    }

    static std::string decimal_to_hex(int decimal_num) {
        if (decimal_num == 0) return "0";
        if (decimal_num < 0) {
            return "-" + decimal_to_hex(-decimal_num);
        }
        std::string hex_str;
        while (decimal_num) {
            int remainder = decimal_num % 16;
            if (remainder < 10) {
                hex_str.push_back('0' + remainder);
            } else {
                hex_str.push_back('a' + (remainder - 10));
            }
            decimal_num /= 16;
        }
        std::reverse(hex_str.begin(), hex_str.end());
        return hex_str;
    }

    static int hex_to_decimal(std::string hex_num) {
        if (hex_num.empty()) {
            throw std::invalid_argument("Empty string");
        }
        if (hex_num[0] == '-') {
            return -hex_to_decimal(hex_num.substr(1));
        }
        int decimal_num = 0;
        for (char c : hex_num) {
            if (c >= '0' && c <= '9') {
                decimal_num = decimal_num * 16 + (c - '0');
            } else if (c >= 'a' && c <= 'f') {
                decimal_num = decimal_num * 16 + (10 + (c - 'a'));
            } else if (c >= 'A' && c <= 'F') {
                decimal_num = decimal_num * 16 + (10 + (c - 'A'));
            } else {
                throw std::invalid_argument("Invalid hex digit");
            }
        }
        return decimal_num;
    }
};