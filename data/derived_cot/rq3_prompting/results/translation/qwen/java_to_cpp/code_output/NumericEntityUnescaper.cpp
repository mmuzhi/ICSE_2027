#include <cctype>
#include <string>
#include <sstream>
#include <stdexcept>

class NumericEntityUnescaper {

public:
    std::string replace(std::string string) {
        std::ostringstream out;
        size_t pos = 0;
        size_t length = string.length();

        while (pos < length - 2) {
            if (string[pos] == '&' && string[pos+1] == '#') {
                pos += 2;
                bool isHex = false;
                if (pos < length && (string[pos] == 'x' || string[pos] == 'X')) {
                    isHex = true;
                    pos++;
                }

                size_t end = pos;
                while (end < length && isHexChar(string[end])) {
                    end++;
                }

                if (end < length && string[end] == ';') {
                    try {
                        if (isHex) {
                            long entityValue = std::stoll(string.substr(pos, end - pos), nullptr, 16);
                            if (entityValue > INT_MAX || entityValue < INT_MIN) {
                                return out.str();
                            }
                            out << static_cast<char>(static_cast<int>(entityValue));
                        } else {
                            int entityValue = std::stoi(string.substr(pos, end - pos), nullptr, 10);
                            out << static_cast<char>(entityValue);
                        }
                        pos = end + 1;
                        continue;
                    } catch (...) {
                        return out.str();
                    }
                }
            }
            out << string[pos];
            pos++;
        }

        return out.str();
    }

    static bool isHexChar(char c) {
        return std::isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    }
};