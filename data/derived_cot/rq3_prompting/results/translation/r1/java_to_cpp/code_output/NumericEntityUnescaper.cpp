#include <string>
#include <stdexcept>
#include <cstdint>

class NumericEntityUnescaper {
public:
    // Replaces numeric HTML entities (&#dec; and &#xhex;) with the corresponding
    // Unicode character. Behaviour matches the original Java code, including the
    // bug that the last two characters of the input are never processed.
    std::u16string replace(const std::u16string& str) {
        std::u16string out;
        int pos = 0;
        int length = static_cast<int>(str.length());

        while (pos < length - 2) {
            if (str[pos] == u'&' && str[pos + 1] == u'#') {
                int start = pos + 2;
                bool isHex = false;
                char16_t firstChar = str[start];

                if (firstChar == u'x' || firstChar == u'X') {
                    ++start;
                    isHex = true;
                }

                if (start == length) {
                    return out;
                }

                int end = start;
                while (end < length && isHexChar(str[end])) {
                    ++end;
                }

                if (end < length && str[end] == u';') {
                    try {
                        // Convert the numeric substring (ASCII digits/letters) to a narrow string
                        // for parsing, because std::stoi does not accept u16string.
                        std::string narrow;
                        for (int i = start; i < end; ++i) {
                            narrow.push_back(static_cast<char>(str[i]));
                        }
                        int entityValue;
                        if (isHex) {
                            entityValue = std::stoi(narrow, nullptr, 16);
                        } else {
                            entityValue = std::stoi(narrow, nullptr, 10);
                        }
                        out.push_back(static_cast<char16_t>(entityValue));
                        pos = end + 1;
                        continue;
                    } catch (const std::exception&) {
                        return out;
                    }
                }
            }
            out.push_back(str[pos]);
            ++pos;
        }

        return out;
    }

    // Checks if a character can be part of a hex number (0-9, a-f, A-F).
    // This mirrors the original Java code (which uses Character.isDigit and
    // manual comparison for a-f). For simplicity we restrict to ASCII digits.
    static bool isHexChar(char16_t c) {
        return (c >= u'0' && c <= u'9') ||
               (c >= u'a' && c <= u'f') ||
               (c >= u'A' && c <= u'F');
    }
};