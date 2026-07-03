#include <string>

class NumberConverter {
public:
    static std::string decimal_to_binary(long long decimal_num) {
        if (decimal_num == 0) return "0";
        bool neg = decimal_num < 0;
        unsigned long long val = neg ? -static_cast<unsigned long long>(decimal_num) : decimal_num;
        std::string res;
        while (val > 0) {
            res = static_cast<char>('0' + val % 2) + res;
            val /= 2;
        }
        if (neg) res = "-" + res;
        return res;
    }

    static long long binary_to_decimal(const std::string& binary_num) {
        return std::stoll(binary_num, nullptr, 2);
    }

    static std::string decimal_to_octal(long long decimal_num) {
        if (decimal_num == 0) return "0";
        bool neg = decimal_num < 0;
        unsigned long long val = neg ? -static_cast<unsigned long long>(decimal_num) : decimal_num;
        std::string res;
        while (val > 0) {
            res = static_cast<char>('0' + val % 8) + res;
            val /= 8;
        }
        if (neg) res = "-" + res;
        return res;
    }

    static long long octal_to_decimal(const std::string& octal_num) {
        return std::stoll(octal_num, nullptr, 8);
    }

    static std::string decimal_to_hex(long long decimal_num) {
        if (decimal_num == 0) return "0";
        bool neg = decimal_num < 0;
        unsigned long long val = neg ? -static_cast<unsigned long long>(decimal_num) : decimal_num;
        std::string res;
        while (val > 0) {
            int rem = val % 16;
            if (rem < 10) res = static_cast<char>('0' + rem) + res;
            else res = static_cast<char>('a' + rem - 10) + res;
            val /= 16;
        }
        if (neg) res = "-" + res;
        return res;
    }

    static long long hex_to_decimal(const std::string& hex_num) {
        return std::stoll(hex_num, nullptr, 16);
    }
};