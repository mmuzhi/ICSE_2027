#include <string>
#include <vector>
#include <map>
#include <variant>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>

class BinaryDataProcessor {
private:
    std::string binary_string;

    bool is_valid_utf8(const std::string& s) {
        int remaining = 0;
        for (unsigned char c : s) {
            if (remaining > 0) {
                if ((c & 0xC0) != 0x80) {
                    return false;
                }
                --remaining;
            } else {
                if (c <= 0x7F) {
                    remaining = 0;
                } else if ((c & 0xE0) == 0xC0) {
                    remaining = 1;
                } else if ((c & 0xF0) == 0xE0) {
                    remaining = 2;
                } else if ((c & 0xF8) == 0xF0) {
                    remaining = 3;
                } else {
                    return false;
                }
            }
        }
        return remaining == 0;
    }

    std::vector<unsigned char> get_bytes() {
        std::vector<unsigned char> bytes;
        size_t length = binary_string.length();
        for (size_t i = 0; i < length; i += 8) {
            size_t end = i + 8;
            if (end > length) {
                end = length;
            }
            std::string byte_str = binary_string.substr(i, end - i);
            char* end_ptr = nullptr;
            unsigned long byte_value = std::strtoul(byte_str.c_str(), &end_ptr, 2);
            if (end_ptr != byte_str.c_str() + byte_str.size()) {
                throw std::runtime_error("Invalid binary digit during conversion");
            }
            bytes.push_back(static_cast<unsigned char>(byte_value));
        }
        return bytes;
    }

public:
    BinaryDataProcessor(std::string binary_string) : binary_string(binary_string) {
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

    using InfoMap = std::map<std::string, std::variant<double, int>>;
    InfoMap calculate_binary_info() {
        int zeroes_count = 0;
        for (char c : binary_string) {
            if (c == '0') {
                zeroes_count++;
            }
        }
        int ones_count = binary_string.length() - zeroes_count;
        int total_length = binary_string.length();
        double zeroes_percentage = (zeroes_count) ? static_cast<double>(zeroes_count) / total_length : 0.0;
        double ones_percentage = (ones_count) ? static_cast<double>(ones_count) / total_length : 0.0;

        InfoMap result;
        result["Zeroes"] = zeroes_percentage;
        result["Ones"] = ones_percentage;
        result["Bit length"] = total_length;

        return result;
    }

    std::string convert_to_ascii() {
        std::vector<unsigned char> bytes = get_bytes();
        for (auto b : bytes) {
            if (b > 127) {
                throw std::runtime_error("Non-ASCII byte encountered");
            }
        }
        return std::string(bytes.begin(), bytes.end());
    }

    std::string convert_to_utf8() {
        std::vector<unsigned char> bytes = get_bytes();
        std::string utf8_string(bytes.begin(), bytes.end());
        if (!is_valid_utf8(utf8_string)) {
            throw std::runtime_error("Invalid UTF-8 sequence");
        }
        return utf8_string;
    }
};