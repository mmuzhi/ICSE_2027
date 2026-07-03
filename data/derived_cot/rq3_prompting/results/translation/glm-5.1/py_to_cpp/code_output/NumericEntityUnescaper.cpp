#include <string>
#include <cctype>
#include <cstdint>
#include <stdexcept>

class NumericEntityUnescaper {
public:
    NumericEntityUnescaper() {}

    std::string replace(const std::string& str) {
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
                        uint32_t entity_value = static_cast<uint32_t>(std::stoul(num_str, nullptr, base));
                        out += code_point_to_utf8(entity_value);
                    } catch (...) {
                        return out;
                    }
                    pos = end + 1;
                    continue;
                }
            }
            out += str[pos];
            pos += 1;
        }

        return out;
    }

    static bool is_hex_char(char c) {
        unsigned char uc = static_cast<unsigned char>(c);
        return std::isdigit(uc) != 0 ||
               (std::tolower(uc) >= 'a' && std::tolower(uc) <= 'f');
    }

private:
    static std::string code_point_to_utf8(uint32_t cp) {
        std::string result;
        if (cp <= 0x7F) {
            result += static_cast<char>(cp);
        } else if (cp <= 0x7FF) {
            result += static_cast<char>(0xC0 | (cp >> 6));
            result += static_cast<char>(0x80 | (cp & 0x3F));
        } else if (cp <= 0xFFFF) {
            result += static_cast<char>(0xE0 | (cp >> 12));
            result += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (cp & 0x3F));
        } else if (cp <= 0x10FFFF) {
            result += static_cast<char>(0xF0 | (cp >> 18));
            result += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
            result += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            result += static_cast<char>(0x80 | (cp & 0x3F));
        }
        return result;
    }
};