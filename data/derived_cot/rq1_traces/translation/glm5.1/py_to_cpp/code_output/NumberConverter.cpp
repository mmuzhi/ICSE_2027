#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

class NumberConverter {
private:
    // Helper function to mimic Python's int(string, base) strictly
    static int string_to_int_base(const std::string& s, int base) {
        if (s.empty()) {
            throw std::invalid_argument("invalid literal for int() with base");
        }
        size_t idx = 0;
        bool negative = false;
        if (s[idx] == '-') {
            negative = true;
            idx++;
        } else if (s[idx] == '+') {
            idx++;
        }
        if (idx == s.size()) {
            throw std::invalid_argument("invalid literal for int() with base");
        }
        
        long long result = 0;
        for (size_t i = idx; i < s.size(); ++i) {
            char c = s[i];
            int digit = -1;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'a' && c <= 'z') {
                digit = c - 'a' + 10;
            } else if (c >= 'A' && c <= 'Z') {
                digit = c - 'A' + 10;
            }
            
            if (digit < 0 || digit >= base) {
                throw std::invalid_argument("invalid literal for int() with base");
            }
            result = result * base + digit;
        }
        if (negative) {
            result = -result;
        }
        return static_cast<int>(result);
    }

public:
    static std::string decimal_to_binary(int decimal_num) {
        if (decimal_num == 0) return "0";
        std::string prefix;
        long long num = decimal_num;
        if (decimal_num < 0) {
            prefix = "b"; // Python's bin(-5)[2:] yields "b101"
            num = -num;
        }
        std::string result;
        while (num > 0) {
            result += (num % 2 ? '1' : '0');
            num /= 2;
        }
        std::reverse(result.begin(), result.end());
        return prefix + result;
    }

    static int binary_to_decimal(const std::string& binary_num) {
        return string_to_int_base(binary_num, 2);
    }

    static std::string decimal_to_octal(int decimal_num) {
        if (decimal_num == 0) return "0";
        std::stringstream ss;
        if (decimal_num < 0) {
            ss << "o" << std::oct << -static_cast<long long>(decimal_num); // Python's oct(-5)[2:] yields "o5"
        } else {
            ss << std::oct << decimal_num;
        }
        return ss.str();
    }

    static int octal_to_decimal(const std::string& octal_num) {
        return string_to_int_base(octal_num, 8);
    }

    static std::string decimal_to_hex(int decimal_num) {
        if (decimal_num == 0) return "0";
        std::stringstream ss;
        if (decimal_num < 0) {
            ss << "x" << std::hex << -static_cast<long long>(decimal_num); // Python's hex(-5)[2:] yields "x5"
        } else {
            ss << std::hex << decimal_num;
        }
        return ss.str();
    }

    static int hex_to_decimal(const std::string& hex_num) {
        return string_to_int_base(hex_num, 16);
    }
};