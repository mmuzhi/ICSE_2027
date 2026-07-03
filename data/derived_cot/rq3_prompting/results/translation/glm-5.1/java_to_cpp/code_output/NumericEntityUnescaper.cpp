#include <string>
#include <cctype>
#include <stdexcept>

class NumericEntityUnescaper {
public:
    static bool isHexChar(char c) {
        auto cu = static_cast<unsigned char>(c);
        return std::isdigit(cu) ||
               ('a' <= std::tolower(cu) && std::tolower(cu) <= 'f');
    }

    std::string replace(const std::string& str) {
        std::string out;
        int pos = 0;
        int length = static_cast<int>(str.length());

        while (pos < length - 2) {
            if (str[pos] == '&' && str[pos + 1] == '#') {
                int start = pos + 2;
                bool isHex = false;
                char firstChar = str[start];

                if (firstChar == 'x' || firstChar == 'X') {
                    start++;
                    isHex = true;
                }

                if (start == length) {
                    return out;
                }

                int end = start;
                while (end < length && isHexChar(str[end])) {
                    end++;
                }

                if (end < length && str[end] == ';') {
                    try {
                        std::string numStr = str.substr(start, end - start);
                        size_t idx;
                        int entityValue = std::stoi(numStr, &idx, isHex ? 16 : 10);
                        if (idx != numStr.length()) {
                            return out;
                        }
                        out += static_cast<char>(entityValue);
                        pos = end + 1;
                        continue;
                    } catch (const std::invalid_argument&) {
                        return out;
                    } catch (const std::out_of_range&) {
                        return out;
                    }
                }
            }
            out += str[pos];
            pos++;
        }

        return out;
    }
};