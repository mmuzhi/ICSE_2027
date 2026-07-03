#include <iostream>
#include <string>

class Manacher {
private:
    std::string inputString;

    std::string preprocess(const std::string& s) {
        std::string sb;
        for (char ch : s) {
            sb.push_back('|');
            sb.push_back(ch);
        }
        sb.push_back('|');
        return sb;
    }

    int palindromicLength(const std::string& s, int center) {
        int diff = 1;
        while (center - diff >= 0 && center + diff < static_cast<int>(s.size()) &&
               s[center - diff] == s[center + diff]) {
            ++diff;
        }
        return diff - 1;
    }

public:
    Manacher(const std::string& inputString) : inputString(inputString) {}

    std::string palindromicString() {
        std::string processedString = preprocess(inputString);
        int maxLength = 0;
        int centerIndex = 0;

        for (int i = 0; i < static_cast<int>(processedString.size()); ++i) {
            int length = palindromicLength(processedString, i);
            if (length > maxLength) {
                maxLength = length;
                centerIndex = i;
            }
        }

        std::string result = processedString.substr(centerIndex - maxLength, 2 * maxLength + 1);
        // Remove all '|' characters
        std::string clean;
        for (char ch : result) {
            if (ch != '|') {
                clean.push_back(ch);
            }
        }
        return clean;
    }
};

int main() {
    Manacher manacher("ababaxse");
    std::cout << manacher.palindromicString() << std::endl;
    return 0;
}