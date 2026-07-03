#include <string>
#include <cctype>
#include <stdexcept>

class NumericEntityUnescaper {
public:
    NumericEntityUnescaper() {}

    std::string replace(const std::string& str) const {
        std::string out;
        int pos = 0;
        int length = static_cast<int>(str.size());

        while (pos < length - 2) {
            if (str[pos] == '&' && str[pos + 1] == '#') {
                int start = pos + 2;
                bool is_hex = false;
                char first_char = str[start];

                if (first_char == 'x' || first_char == 'X') {
                    start += 1;
                    is_hex = true;
                }

                if (start == length) {
                    return out;
                }

                int end = start;
                while (end < length && is_hex_char(str[end])) {
                    end += 1;
                }

                if (end < length && str[end] == ';') {
                    try {
                        std::string num_str = str.substr(start, end - start);
                        int base = is_hex ? 16 : 10;
                        unsigned long entity_value = std::stoul(num_str, nullptr, base);
                        if (entity_value > 0x10FFFF) {
                            throw std::runtime_error("code point out of range");
                        }
                        out += code_point_to_utf8(static_cast<unsigned int>(entity_value));
                        pos = end + 1;
                        continue;
                    } catch (...) {
                        return out;
                    }
                }
            }
            out += str[pos];
            pos += 1;
        }

        return out;
    }

    static bool is_hex_char(char c) {
        unsigned char uc = static_cast<unsigned char>(c);
        return std::isdigit(uc) ||
               (std::tolower(uc) >= 'a' && std::tolower(uc) <= 'f');
    }

private:
    static std::string code_point_to_utf8(unsigned int code_point) {
        std::string result;
        if (code_point <= 0x7F) {
            result += static_cast<char>(code_point);
        } else if (code_point <= 0x7FF) {
            result += static_cast<char>(0xC0 | (code_point >> 6));
            result += static_cast<char>(0x80 | (code_point & 0x3F));
        } else if (code_point <= 0xFFFF) {
            result += static_cast<char>(0xE0 | (code_point >> 12));
            result += static_cast<char>(0x80 | ((code_point >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (code_point & 0x3F));
        } else {
            result += static_cast<char>(0xF0 | (code_point >> 18));
            result += static_cast<char>(0x80 | ((code_point >> 12) & 0x3F));
            result += static_cast<char>(0x80 | ((code_point >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (code_point & 0x3F));
        }
        return result;
    }
};