#include <string>
#include <bitset>
#include <sstream>
#include <stdexcept>

namespace org_example {

class NumberConverter {
public:
    static std::string decimal_to_binary(int decimalNum) {
        if (decimalNum == 0) {
            return "0";
        }
        if (decimalNum < 0) {
            std::bitset<32> bits(decimalNum);
            return bits.to_string();
        }
        std::string s;
        int n = decimalNum;
        while (n) {
            s.insert(s.begin(), (n & 1) ? '1' : '0');
            n >>= 1;
        }
        return s;
    }

    static int binary_to_decimal(const std::string& binaryNum) {
        return std::stoi(binaryNum, nullptr, 2);
    }

    static std::string decimal_to_octal(int decimalNum) {
        std::ostringstream oss;
        oss << std::oct << decimalNum;
        return oss.str();
    }

    static int octal_to_decimal(const std::string& octalNum) {
        return std::stoi(octalNum, nullptr, 8);
    }

    static std::string decimal_to_hex(int decimalNum) {
        std::ostringstream oss;
        oss << std::hex << decimalNum;
        return oss.str();
    }

    static int hex_to_decimal(const std::string& hexNum) {
        return std::stoi(hexNum, nullptr, 16);
    }
};

} // namespace org_example