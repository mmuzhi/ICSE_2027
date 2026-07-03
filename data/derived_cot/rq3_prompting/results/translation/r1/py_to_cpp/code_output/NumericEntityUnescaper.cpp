#include <string>
#include <cctype>
#include <stdexcept>

class NumericEntityUnescaper {
public:
    NumericEntityUnescaper() = default;

    std::string replace(const std::string& string) {
        std::string out;
        size_t pos = 0;
        size_t length = string.size();

        while (pos < length - 2) {  // need at least 2 characters after pos
            if (string[pos] == '&' && string[pos + 1] == '#') {
                size_t start = pos + 2;
                bool is_hex = false;
                char first_char = string[start];

                if (first_char == 'x' || first_char == 'X') {
                    ++start;
                    is_hex = true;
                }

                if (start == length) {
                    return out;
                }

                size_t end = start;
                while (end < length && is_hex_char(string[end])) {
                    ++end;
                }

                if (end < length && string[end] == ';') {
                    try {
                        std::string num_str = string.substr(start, end - start);
                        int base = is_hex ? 16 : 10;
                        int entity_value = std::stoi(num_str, nullptr, base);
                        out.push_back(static_cast<char>(entity_value));
                        pos = end + 1;
                        continue;
                    } catch (const std::exception&) {
                        return out;
                    }
                }
            }

            out.push_back(string[pos]);
            ++pos;
        }

        return out;
    }

    static bool is_hex_char(char c) {
        return std::isdigit(c) || (std::tolower(c) >= 'a' && std::tolower(c) <= 'f');
    }
};