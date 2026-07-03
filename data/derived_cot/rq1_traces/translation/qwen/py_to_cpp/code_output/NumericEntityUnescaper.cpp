#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <locale>
#include <algorithm>

class NumericEntityUnescaper {
public:
    std::string replace(const std::string& input) {
        std::string result;
        size_t pos = 0;
        size_t len = input.length();

        while (pos < len - 2) {
            if (input[pos] == '&' && input[pos+1] == '#') {
                size_t start = pos + 2;
                bool is_hex = false;

                if (start < len) {
                    char c = input[start];
                    if (c == 'x' || c == 'X') {
                        start++;
                        is_hex = true;
                    }
                }

                if (start >= len) {
                    return result;
                }

                size_t end = start;
                while (end < len && NumericEntityUnescaper::is_hex_char(input[end])) {
                    end++;
                }

                if (end < len && input[end] == ';') {
                    try {
                        std::string substr = input.substr(start, end - start);
                        int entity_value = std::stoi(substr, nullptr, is_hex ? 16 : 10);
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
        if (std::isdigit(c)) {
            return true;
        }
        char lower_c = std::tolower(c);
        return lower_c >= 'a' && lower_c <= 'f';
    }
};