#include <string>
#include <stdexcept>

class NumericEntityUnescaper {
public:
    std::u16string replace(const std::u16string& str) {
        std::u16string out;
        size_t pos = 0;
        size_t length = str.length();

        while (pos < length - 2) {
            if (str[pos] == u'&' && str[pos + 1] == u'#') {
                size_t start = pos + 2;
                bool isHex = false;

                if (start < length) {
                    char16_t firstChar = str[start];
                    if (firstChar == u'x' || firstChar == u'X') {
                        start++;
                        isHex = true;
                    }
                }

                if (start == length) {
                    return out;
                }

                size_t end = start;
                while (end < length && isHexChar(str[end])) {
                    end++;
                }

                if (end < length && str[end] == u';') {
                    std::u16string numStr = str.substr(start, end - start);
                    std::string numStrAscii;
                    for (char16_t c : numStr) {
                        numStrAscii.push_back(static_cast<char>(c));
                    }

                    try {
                        int base = isHex ? 16 : 10;
                        int entityValue = std::stoi(numStrAscii, nullptr, base);
                        out.push_back(static_cast<char16_t>(entityValue));
                        pos = end + 1;
                        continue;
                    } catch (const std::invalid_argument& e) {
                        return out;
                    } catch (const std::out_of_range& e) {
                        return out;
                    }
                }
            }
            out.push_back(str[pos]);
            pos++;
        }

        return out;
    }

private:
    static bool isHexChar(char16_t c) {
        return (c >= u'0' && c <= u'9') ||
               (c >= u'a' && c <= u'f') ||
               (c >= u'A' && c <= u'F');
    }
};