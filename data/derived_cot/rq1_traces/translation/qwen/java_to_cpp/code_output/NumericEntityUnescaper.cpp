#include <string>
#include <cctype>
#include <stdexcept>

class NumericEntityUnescaper {
public:
    static bool isHexChar(char c) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            return true;
        }
        char lower = std::tolower(static_cast<unsigned char>(c));
        return (lower >= 'a' && lower <= 'f');
    }

    std::string replace(const std::string& input) {
        std::string out;
        int pos = 0;
        int length = input.length();

        while (pos < length - 2) {
            if (input[pos] == '&' && input[pos+1] == '#') {
                int start = pos + 2;
                bool isHex = false;

                if (start < length && (input[start] == 'x' || input[start] == 'X')) {
                    start++;
                    isHex = true;
                }

                if (start >= length) {
                    return out;
                }

                int end = start;
                while (end < length && isHexChar(input[end])) {
                    end++;
                }

                if (end < length && input[end] == ';') {
                    try {
                        std::string numStr = input.substr(start, end - start);
                        int entityValue;
                        if (isHex) {
                            entityValue = std::stoi(numStr, nullptr, 16);
                        } else {
                            entityValue = std::stoi(numStr, nullptr, 10);
                        }
                        out.push_back(static_cast<char>(entityValue));
                        pos = end + 1;
                        continue;
                    } catch (...) {
                        return out;
                    }
                }
            }
            out.push_back(input[pos]);
            pos++;
        }

        return out;
    }
};