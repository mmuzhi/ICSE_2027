#include <string>
#include <bitset>
#include <cstdint>
#include <sstream>
#include <stdexcept>

class NumberConverter {
private:
    // Helper method to replicate the strict parsing behavior of Integer.parseInt(String, radix)
    static int32_t parseInt(const std::string& s, int radix) {
        if (radix < 2 || radix > 36) {
            throw std::invalid_argument("Radix out of range");
        }
        if (s.empty()) {
            throw std::invalid_argument("Empty string");
        }

        bool negative = false;
        size_t i = 0;
        
        if (s[0] == '-') {
            negative = true;
            i = 1;
        }
        
        if (i == s.size()) {
            throw std::invalid_argument("No digits to parse");
        }

        int64_t result = 0;
        for (; i < s.size(); ++i) {
            int digit = -1;
            char c = s[i];
            
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c >= 'A' && c <= 'Z') {
                digit = c - 'A' + 10;
            } else if (c >= 'a' && c <= 'z') {
                digit = c - 'a' + 10;
            }

            // Disallow invalid characters, plus signs, and whitespace
            if (digit < 0 || digit >= radix) {
                throw std::invalid_argument("Invalid character in input string");
            }

            // Check for int64_t overflow before multiplying/adding
            if (result > (INT64_MAX - digit) / radix) {
                throw std::out_of_range("Input string too long");
            }
            
            result = result * radix + digit;

            // Check for 32-bit signed bounds
            if (negative) {
                if (-result < INT32_MIN) {
                    throw std::out_of_range("Result out of range for int32_t");
                }
            } else {
                if (result > INT32_MAX) {
                    throw std::out_of_range("Result out of range for int32_t");
                }
            }
        }

        return negative ? static_cast<int32_t>(-result) : static_cast<int32_t>(result);
    }

public:
    static std::string decimalToBinary(int32_t decimalNum) {
        // std::bitset constructs from unsigned bits, perfectly mimicking Java's two's complement representation
        std::string s = std::bitset<32>(static_cast<uint32_t>(decimalNum)).to_string();
        
        // Strip leading zeros for positive numbers, but keep at least one digit if the number is 0
        size_t first_one = s.find('1');
        if (first_one == std::string::npos) {
            return "0";
        }
        return s.substr(first_one);
    }

    static int32_t binaryToDecimal(const std::string& binaryNum) {
        return parseInt(binaryNum, 2);
    }

    static std::string decimalToOctal(int32_t decimalNum) {
        std::stringstream ss;
        // Casting to uint32_t mimics Java's unsigned interpretation for negative decimals
        ss << std::oct << static_cast<uint32_t>(decimalNum);
        return ss.str();
    }

    static int32_t octalToDecimal(const std::string& octalNum) {
        return parseInt(octalNum, 8);
    }

    static std::string decimalToHex(int32_t decimalNum) {
        std::stringstream ss;
        // Casting to uint32_t mimics Java's unsigned interpretation for negative decimals
        ss << std::hex << static_cast<uint32_t>(decimalNum);
        return ss.str();
    }

    static int32_t hexToDecimal(const std::string& hexNum) {
        return parseInt(hexNum, 16);
    }
};