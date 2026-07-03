#include <string>
#include <map>
#include <algorithm>
#include <stdexcept>

class BinaryDataProcessor {
public:
    std::string binary_string;

    BinaryDataProcessor(const std::string& binary_string) : binary_string(binary_string) {
        clean_non_binary_chars();
    }

    void clean_non_binary_chars() {
        binary_string.erase(
            std::remove_if(binary_string.begin(), binary_string.end(),
                [](char c) { return c != '0' && c != '1'; }),
            binary_string.end()
        );
    }

    std::map<std::string, double> calculate_binary_info() {
        int zeroes_count = std::count(binary_string.begin(), binary_string.end(), '0');
        int ones_count = std::count(binary_string.begin(), binary_string.end(), '1');
        int total_length = static_cast<int>(binary_string.size());

        if (total_length == 0) {
            throw std::runtime_error("ZeroDivisionError");
        }

        double zeroes_percentage = static_cast<double>(zeroes_count) / total_length;
        double ones_percentage = static_cast<double>(ones_count) / total_length;

        return {
            {"Zeroes", zeroes_percentage},
            {"Ones", ones_percentage},
            {"Bit length", static_cast<double>(total_length)}
        };
    }

    std::string convert_to_ascii() {
        std::string result;
        for (size_t i = 0; i < binary_string.size(); i += 8) {
            std::string byte_str = binary_string.substr(i, 8);
            int decimal = std::stoi(byte_str, nullptr, 2);
            result += static_cast<char>(decimal);
        }
        return result;
    }

    std::string convert_to_utf8() {
        std::string result;
        for (size_t i = 0; i < binary_string.size(); i += 8) {
            std::string byte_str = binary_string.substr(i, 8);
            int decimal = std::stoi(byte_str, nullptr, 2);
            result += static_cast<char>(decimal);
        }
        return result;
    }
};