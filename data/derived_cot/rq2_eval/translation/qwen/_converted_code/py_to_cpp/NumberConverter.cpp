#include <string>
#include <cmath>
#include <cctype>
#include <iostream>

class NumberConverter {
public:
    static std::string decimal_to_binary(int decimal_num) {
        if (decimal_num == 0) {
            return "0";
        }
        std::string binary = "";
        int n = decimal_num;
        while (n > 0) {
            int remainder = n % 2;
            binary = std::to_string(remainder) + binary;
            n = n / 2;
        }
        return binary;
    }

    static int binary_to_decimal(const std::string& binary_num) {
        int decimal = 0;
        int length = binary_num.length();
        for (int i = 0; i < length; i++) {
            if (binary_num[i] == '1') {
                decimal += std::pow(2, length - i - 1);
            }
        }
        return decimal;
    }

    static std::string decimal_to_octal(int decimal_num) {
        if (decimal_num == 0) {
            return "0";
        }
        std::string octal = "";
        int n = decimal_num;
        while (n > 0) {
            int remainder = n % 8;
            octal = std::to_string(remainder) + octal;
            n = n / 8;
        }
        return octal;
    }

    static int octal_to_decimal(const std::string& octal_num) {
        int decimal = 0;
        int length = octal_num.length();
        for (int i = 0; i < length; i++) {
            if (octal_num[i] >= '0' && octal_num[i] <= '7') {
                decimal += (octal_num[i] - '0') * std::pow(8, length - i - 1);
            }
        }
        return decimal;
    }

    static std::string decimal_to_hex(int decimal_num) {
        if (decimal_num == 0) {
            return "0";
        }
        std::string hex = "";
        int n = decimal_num;
        while (n > 0) {
            int remainder = n % 16;
            if (remainder < 10) {
                hex = std::to_string(remainder) + hex;
            } else {
                char hex_digit = 'a' + (remainder - 10);
                hex = std::string(1, hex_digit) + hex;
            }
            n = n / 16;
        }
        return hex;
    }

    static int hex_to_decimal(const std::string& hex_num) {
        int decimal = 0;
        int length = hex_num.length();
        for (int i = 0; i < length; i++) {
            char c = hex_num[i];
            int value;
            if (c >= '0' && c <= '9') {
                value = c - '0';
            } else if (c >= 'a' && c <= 'f') {
                value = c - 'a' + 10;
            } else if (c >= 'A' && c <= 'F') {
                value = c - 'A' + 10;
            } else {
                // Handle invalid characters if necessary
                continue;
            }
            decimal += value * std::pow(16, length - i - 1);
        }
        return decimal;
    }
};