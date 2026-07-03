#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

class BinaryDataProcessor {
private:
    std::string binary_string;

public:
    BinaryDataProcessor(const std::string& binary_string) {
        this->binary_string = binary_string;
        cleanNonBinaryChars();
    }

    void cleanNonBinaryChars() {
        binary_string.erase(std::remove_if(binary_string.begin(), binary_string.end(), 
            [](unsigned char c) { 
                return !std::isdigit(c) || (c != '0' && c != '1'); 
            }), 
            binary_string.end());
    }

    struct BinaryInfo {
        double zeroes;
        double ones;
        size_t bit_length;
    };

    BinaryInfo calculateBinaryInfo() {
        if (binary_string.empty()) {
            return {0.0, 0.0, 0};
        }

        size_t zeroes_count = 0;
        size_t ones_count = 0;
        for (char c : binary_string) {
            if (c == '0') zeroes_count++;
            else if (c == '1') ones_count++;
        }

        size_t total_length = binary_string.length();
        double zeroes_percentage = static_cast<double>(zeroes_count) / total_length;
        double ones_percentage = static_cast<double>(ones_count) / total_length;

        return {zeroes_percentage, ones_percentage, total_length};
    }

    std::string convertToASCII() {
        std::vector<unsigned char> byte_array;
        for (size_t i = 0; i < binary_string.length(); i += 8) {
            if (i + 8 > binary_string.length()) break;

            std::string byte_str = binary_string.substr(i, 8);
            try {
                unsigned char byte = static_cast<unsigned char>(std::stoll(byte_str, nullptr, 2));
                byte_array.push_back(byte);
            } catch (...) {
                throw std::invalid_argument("Invalid binary substring in convertToASCII");
            }
        }

        return std::string(byte_array.begin(), byte_array.end());
    }

    std::string convertToUTF8() {
        std::vector<unsigned char> byte_array;
        for (size_t i = 0; i < binary_string.length(); i += 8) {
            if (i + 8 > binary_string.length()) break;

            std::string byte_str = binary_string.substr(i, 8);
            try {
                unsigned char byte = static_cast<unsigned char>(std::stoll(byte_str, nullptr, 2));
                byte_array.push_back(byte);
            } catch (...) {
                throw std::invalid_argument("Invalid binary substring in convertToUTF8");
            }
        }

        return std::string(byte_array.begin(), byte_array.end());
    }
};