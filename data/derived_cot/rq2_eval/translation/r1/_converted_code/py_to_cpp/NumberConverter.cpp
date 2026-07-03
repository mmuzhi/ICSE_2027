#include <string>
#include <utility>
#include <cctype>
#include <sstream>
#include <iostream>

class NumberConverter {
private:
    static std::string multiply_string_by_int(const std::string& num, int multiplier) {
        if (multiplier == 0) {
            return "0";
        }
        if (multiplier == 1) {
            return num;
        }

        std::string result;
        int carry = 0;
        for (int i = num.size() - 1; i >= 0; i--) {
            int digit = num[i] - '0';
            int product = digit * multiplier + carry;
            carry = product / 10;
            int d = product % 10;
            result = char('0' + d) + result;
        }
        while (carry) {
            result = char('0' + carry % 10) + result;
            carry /= 10;
        }
        return result;
    }

    static std::string add_digit_to_string(const std::string& num, int digit) {
        if (digit == 0) {
            return num;
        }

        std::string result;
        int carry = digit;
        int i = num.size() - 1;
        while (i >= 0 || carry) {
            int d = 0;
            if (i >= 0) {
                d = num[i] - '0';
                i--;
            }
            int s = d + carry;
            carry = s / 10;
            result = char('0' + (s % 10)) + result;
        }
        return result;
    }

    static std::pair<std::string, int> divide_string_by_int(const std::string& num, int divisor) {
        if (num == "0") {
            return std::make_pair("0", 0);
        }

        std::string quotient;
        int remainder = 0;
        for (size_t i = 0; i < num.size(); i++) {
            char c = num[i];
            int current = remainder * 10 + (c - '0');
            int q = current / divisor;
            remainder = current % divisor;
            if (q == 0 && quotient.empty()) {
                continue;
            }
            quotient += char('0' + q);
        }
        if (quotient.empty()) {
            quotient = "0";
        }
        return std::make_pair(quotient, remainder);
    }

    static std::string base_to_decimal_string(const std::string& num_str, int base) {
        std::string result = "0";
        for (char c : num_str) {
            int digit;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'a' && c <= 'f') {
                digit = 10 + (c - 'a');
            } else if (c >= 'A' && c <= 'F') {
                digit = 10 + (c - 'A');
            } else {
                digit = 0;
            }
            result = multiply_string_by_int(result, base);
            result = add_digit_to_string(result, digit);
        }
        return result;
    }

    static std::string decimal_string_to_base(const std::string& decimal_num, int base) {
        if (decimal_num == "0") {
            return "0";
        }

        std::string num = decimal_num;
        std::string result;
        while (num != "0") {
            auto [quotient, remainder] = divide_string_by_int(num, base);
            num = quotient;
            char c;
            if (remainder < 10) {
                c = '0' + remainder;
            } else {
                c = 'a' + (remainder - 10);
            }
            result = c + result;
        }
        return result;
    }

public:
    static std::string decimal_to_binary(const std::string& decimal_num) {
        return decimal_string_to_base(decimal_num, 2);
    }

    static std::string decimal_to_binary(long long decimal_num) {
        return decimal_to_binary(std::to_string(decimal_num));
    }

    static std::string binary_to_decimal(const std::string& binary_num) {
        return base_to_decimal_string(binary_num, 2);
    }

    static std::string decimal_to_octal(const std::string& decimal_num) {
        return decimal_string_to_base(decimal_num, 8);
    }

    static std::string decimal_to_octal(long long decimal_num) {
        return decimal_to_octal(std::to_string(decimal_num));
    }

    static std::string octal_to_decimal(const std::string& octal_num) {
        return base_to_decimal_string(octal_num, 8);
    }

    static std::string decimal_to_hex(const std::string& decimal_num) {
        return decimal_string_to_base(decimal_num, 16);
    }

    static std::string decimal_to_hex(long long decimal_num) {
        return decimal_to_hex(std::to_string(decimal_num));
    }

    static std::string hex_to_decimal(const std::string& hex_num) {
        return base_to_decimal_string(hex_num, 16);
    }
};