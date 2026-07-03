#include <iostream>
#include <string>
#include <vector>

class Manacher {
private:
    std::string inputString;

    std::string preprocess(const std::string& s) {
        std::string result;
        for (char c : s) {
            result += '|';
            result += c;
        }
        result += '|';
        return result;
    }

    int palindromicLength(const std::string& s, int center) {
        int diff = 1;
        while (center - diff >= 0 && center + diff < static_cast<int>(s.length()) && 
               s[center - diff] == s[center + diff]) {
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

        for (int i = 0; i < processedString.length(); i++) {
            int length = palindromicLength(processedString, i);
            if (length > maxLength) {
                maxLength = length;
                centerIndex = i;
            }
        }

        std::string result = processedString.substr(centerIndex - maxLength, 2 * maxLength + 1);
        for (char c : result) {
            if (c != '|') {
                result.erase(std::remove(result.begin(), result.end(), '|'), result.end());
                break; // Only one removal pass needed
            }
        }
        return result;
    }
};

int main() {
    Manacher manacher("ababaxse");
    std::cout << manacher.palindromicString() << std::endl;
    return 0;
}