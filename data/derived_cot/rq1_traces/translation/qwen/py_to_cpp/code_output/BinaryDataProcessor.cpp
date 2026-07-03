#include <string>
#include <vector>
#include <algorithm>
#include <locale>

class BinaryDataProcessor {
private:
    std::string binary_string;

    void clean_non_binary_chars() {
        binary_string.erase(std::remove_if(binary_string.begin(), binary_string.end(),
            [](unsigned char c) { return c != '0' && c != '1'; }),
            binary_string.end());
    }

public:
    BinaryDataProcessor(const std::string& binary_string) {
        this->binary_string = binary_string;
        clean_non_binary_chars();
    }

    struct BinaryInfo {
        double Zeroes;
        double Ones;
        int Bit_length;
    };

    BinaryInfo calculate_binary_info() {
        int zeroes_count = 0;
        int ones_count = 0;
        int total_length = binary_string.length();

        for (char c : binary_string) {
            if (c == '0') zeroes_count++;
            else if (c == '1') ones_count++;
        }

        double zeroes_percentage = static_cast<double>(zeroes_count) / total_length;
        double ones_percentage = static_cast<double>(ones_count) / total_length;

        return {
            Zeroes: zeroes_percentage,
            Ones: ones_percentage,
            Bit_length: total_length
        };
    }

    std::wstring convert_to_ascii() {
        std::vector<unsigned char> byte_array;
        for (size_t i = 0; i < binary_string.length(); i += 8) {
            std::string byte_str = binary_string.substr(i, 8);
            if (byte_str.empty()) break;

            try {
                unsigned char decimal = static_cast<unsigned char>(std::stoi(byte_str, nullptr, 2));
                byte_array.push_back(decimal);
            } catch (...) {
                break;
            }
        }

        std::wstring_convert<std::codecvt_utf8<unsigned char>> converter;
        return converter.from_bytes(byte_array.data(), byte_array.data() + byte_array.size());
    }

    std::wstring convert_to_utf8() {
        std::vector<unsigned char> byte_array;
        for (size_t i = 0; i < binary_string.length(); i += 8) {
            std::string byte_str = binary_string.substr(i, 8);
            if (byte_str.empty()) break;

            try {
                unsigned char decimal = static_cast<unsigned char>(std::stoi(byte_str, nullptr, 2));
                byte_array.push_back(decimal);
            } catch (...) {
                break;
            }
        }

        std::wstring_convert<std::codecvt_utf8<unsigned char>> converter;
        return converter.from_bytes(byte_array.data(), byte_array.data() + byte_array.size());
    }
};