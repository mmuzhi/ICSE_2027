#include <string>
#include <stdexcept>
#include <cctype>

class NumericEntityUnescaper {
public:
    std::string replace(const std::string& input) {
        std::string result;
        size_t pos = 0;
        size_t length = input.length();

        while (pos < length - 2) {
            if (input[pos] == '&' && input[pos + 1] == '#') {
                size_t start = pos + 2;
                bool is_hex = false;
                char first_char = input[start];

                if (first_char == 'x' || first_char == 'X') {
                    start++;
                    is_hex = true;
                }

                if (start >= length) {
                    return result;
                }

                size_t end = start;
                while (end < length && is_hex_char(input[end])) {
                    end++;
                }

                if (end < length && input[end] == ';') {
                    try {
                        std::string num_str = input.substr(start, end - start);
                        unsigned long long entity_value;
                        if (is_hex) {
                            entity_value = std::stoull(num_str, nullptr, 16);
                        } else {
                            entity_value = std::stoull(num_str, nullptr, 10);
                        }
                        result += static_cast<char>(entity_value);
                        pos = end + 1;
                        continue;
                    } catch (...) {
                        return result;
                    }
                }
            }
            result += input[pos];
            pos++;
        }

        return result;
    }

    static bool is_hex_char(char c) {
        return (c >= '0' && c <= '9') ||
               (c >= 'a' && c <= 'f') ||
               (c >= 'A' && c <= 'F');
    }
};