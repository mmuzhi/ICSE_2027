#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>

class BinaryDataProcessor {
public:
    std::string binary_string;

    BinaryDataProcessor(const std::string& binary_string) : binary_string(binary_string) {
        clean_non_binary_chars();
    }

    void clean_non_binary_chars() {
        std::string cleaned;
        cleaned.reserve(binary_string.size());
        for (char c : binary_string) {
            if (c == '0' || c == '1') {
                cleaned += c;
            }
        }
        binary_string = std::move(cleaned);
    }

    std::map<std::string, double> calculate_binary_info() {
        auto zeroes_count = std::count(binary_string.begin(), binary_string.end(), '0');
        auto ones_count = std::count(binary_string.begin(), binary_string.end(), '1');
        size_t total_length = binary_string.size();

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
            unsigned long decimal = binary_to_ulong(byte_str);
            if (decimal > 127) {
                throw std::runtime_error("UnicodeDecodeError");
            }
            result += static_cast<char>(decimal);
        }
        return result;
    }

    std::string convert_to_utf8() {
        std::string result;
        for (size_t i = 0; i < binary_string.size(); i += 8) {
            std::string byte_str = binary_string.substr(i, 8);
            unsigned long decimal = binary_to_ulong(byte_str);
            result += static_cast<char>(decimal);
        }
        validate_utf8(result);
        return result;
    }

private:
    unsigned long binary_to_ulong(const std::string& s) {
        unsigned long result = 0;
        for (char c : s) {
            result = (result << 1) + (c - '0');
        }
        return result;
    }

    void validate_utf8(const std::string& str) {
        for (size_t i = 0; i < str.size(); ) {
            unsigned char c = str[i];
            int num_bytes = 0;

            if ((c & 0x80) == 0x00) {
                num_bytes = 1;
            } else if ((c & 0xE0) == 0xC0) {
                num_bytes = 2;
            } else if ((c & 0xF0) == 0xE0) {
                num_bytes = 3;
            } else if ((c & 0xF8) == 0xF0) {
                num_bytes = 4;
            } else {
                throw std::runtime_error("UnicodeDecodeError");
            }

            if (i + num_bytes > str.size()) {
                throw std::runtime_error("UnicodeDecodeError");
            }

            for (int j = 1; j < num_bytes; ++j) {
                if ((static_cast<unsigned char>(str[i + j]) & 0xC0) != 0x80) {
                    throw std::runtime_error("UnicodeDecodeError");
                }
            }
            
            // Check for overlong encodings and invalid code points (surrogates/out of range)
            if (num_bytes == 2) {
                if ((c & 0x1E) == 0) throw std::runtime_error("UnicodeDecodeError");
            } else if (num_bytes == 3) {
                if ((c & 0x0F) == 0 && (static_cast<unsigned char>(str[i+1]) & 0x20) == 0) throw std::runtime_error("UnicodeDecodeError");
                if (c == 0xED && (static_cast<unsigned char>(str[i+1]) & 0x20) != 0) throw std::runtime_error("UnicodeDecodeError");
            } else if (num_bytes == 4) {
                if ((c & 0x07) == 0 && (static_cast<unsigned char>(str[i+1]) & 0x30) == 0) throw std::runtime_error("UnicodeDecodeError");
                if (c > 0xF4 || (c == 0xF4 && (static_cast<unsigned char>(str[i+1]) & 0x30) != 0)) throw std::runtime_error("UnicodeDecodeError");
            }

            i += num_bytes;
        }
    }
};