#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

class BinaryDataProcessor {
public:
    std::string binary_string;

    BinaryDataProcessor(const std::string& binary_string)
        : binary_string(binary_string) {
        clean_non_binary_chars();
    }

    void clean_non_binary_chars() {
        std::string cleaned;
        for (char c : binary_string) {
            if (c == '0' || c == '1') {
                cleaned += c;
            }
        }
        binary_string = cleaned;
    }

    std::map<std::string, double> calculate_binary_info() {
        int zeros = 0, ones = 0;
        for (char c : binary_string) {
            if (c == '0') zeros++;
            else if (c == '1') ones++;
        }
        int total = zeros + ones;
        if (total == 0) {
            throw std::domain_error("division by zero"); // matches Python's ZeroDivisionError
        }
        double zero_percent = static_cast<double>(zeros) / total;
        double one_percent = static_cast<double>(ones) / total;
        return {
            {"Zeroes", zero_percent},
            {"Ones", one_percent},
            {"Bit length", static_cast<double>(total)}
        };
    }

    std::string convert_to_ascii() {
        std::string result;
        for (size_t i = 0; i < binary_string.size(); i += 8) {
            std::string byte_str = binary_string.substr(i, 8);
            int decimal = std::stoi(byte_str, nullptr, 2);
            result.push_back(static_cast<char>(decimal));
        }
        return result;
    }

    std::string convert_to_utf8() {
        return convert_to_ascii(); // identical implementation
    }
};