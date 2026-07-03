#include <string>
#include <cctype>
#include <stdexcept>
#include <cstdlib>

class NumericEntityUnescaper {
public:
    NumericEntityUnescaper() {}

    std::string replace(const std::string& string) {
        size_t len = string.length();
        if (len < 3) {
            return "";
        }

        std::string out_string;
        size_t pos = 0;

        while (pos < len - 2) {
            if (string[pos] == '&' && string[pos + 1] == '#') {
                size_t start = pos + 2;
                bool is_hex = false;
                char first_char = string[start];

                if (first_char == 'x' || first_char == 'X') {
                    start++;
                    is_hex = true;
                }

                if (start == len) {
                    return out_string;
                }

                size_t end = start;
                while (end < len && is_hex_char(string[end])) {
                    end++;
                }

                if (end < len && string[end] == ';') {
                    try {
                        int base = is_hex ? 16 : 10;
                        std::string num_str = string.substr(start, end - start);
                        size_t idx;
                        unsigned long value = std::stoul(num_str, &idx, base);

                        if (idx != num_str.length()) {
                            throw std::invalid_argument("Invalid character in number");
                        }

                        if (value > 0x10FFFF) {
                            throw std::out_of_range("Code point out of range");
                        }

                        std::string utf8_char = to_utf8(static_cast<uint32_t>(value));
                        out_string += utf8_char;
                        pos = end + 1;
                        continue;
                    } catch (...) {
                        return out_string;
                    }
                }
            }

            out_string.push_back(string[pos]);
            pos++;
        }

        return out_string;
    }

    static bool is_hex_char(char c) {
        return (c >= '0' && c <= '9') ||
               (c >= 'a' && c <= 'f') ||
               (c >= 'A' && c <= 'F');
    }

private:
    static std::string to_utf8(uint32_t code_point) {
        std::string out;
        if (code_point <= 0x7F) {
            out.push_back(static_cast<char>(code_point));
        } else if (code_point <= 0x7FF) {
            out.push_back(static_cast<char>(0xC0 | (code_point >> 6)));
            out.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
        } else if (code_point <= 0xFFFF) {
            out.push_back(static_cast<char>(0xE0 | (code_point >> 12)));
            out.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3F)));
            out.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
        } else if (code_point <= 0x10FFFF) {
            out.push_back(static_cast<char>(0xF0 | (code_point >> 18)));
            out.push_back(static_cast<char>(0x80 | ((code_point >> 12) & 0x3F)));
            out.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3F)));
            out.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
        }
        return out;
    }
};