#include <iostream>
#include <string>

class Manacher {
private:
    std::string inputString;

    std::string preprocess(const std::string& s) {
        std::string result;
        for (size_t i = 0; i < s.length(); i++) {
            result += '|';
            result += s[i];
        }
        result += '|';
        return result;
    }

protected:
    int palindromicLength(const std::string& s, int center) {
        int diff = 1;
        while (center - diff >= 0 && center + diff < (int)s.length() && s[center - diff] == s[center + diff]) {
            diff++;
        }
        return diff - 1;
    }

public:
    Manacher(const std::string& inputString) : inputString(inputString) {}

    std::string palindromicString() {
        std::string processedString = preprocess(inputString);
        int maxLength = 0;
        int centerIndex = 0;

        for (int i = 0; i < (int)processedString.length(); i++) {
            int length = palindromicLength(processedString, i);
            if (length > maxLength) {
                maxLength = length;
                centerIndex = i;
            }
        }

        std::string result = processedString.substr(centerIndex - maxLength, 2 * maxLength + 1);
        std::string cleaned;
        for (char c : result) {
            if (c != '|') cleaned += c;
        }
        return cleaned;
    }
};

int main() {
    Manacher manacher("ababaxse");
    std::cout << manacher.palindromicString() << std::endl;
    return 0;
}