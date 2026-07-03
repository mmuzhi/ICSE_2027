#include <iostream>
#include <string>
#include <algorithm>

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

    int palindromic_length(const std::string& s, int center) {
        int diff = 1;
        int n = static_cast<int>(s.length());
        while (center - diff >= 0 && center + diff < n && s[center - diff] == s[center + diff]) {
            diff++;
        }
        return diff - 1;
    }

public:
    Manacher(const std::string& s) : inputString(s) {}

    std::string palindromic_string() {
        std::string processedString = preprocess(inputString);
        int maxLength = 0;
        int centerIndex = 0;

        int n = static_cast<int>(processedString.length());
        for (int i = 0; i < n; i++) {
            int length = palindromic_length(processedString, i);
            if (length > maxLength) {
                maxLength = length;
                centerIndex = i;
            }
        }

        int start = centerIndex - maxLength;
        int len = 2 * maxLength + 1;
        std::string result = processedString.substr(start, len);
        result.erase(std::remove(result.begin(), result.end(), '|'), result.end());
        return result;
    }
};

int main() {
    Manacher manacher("ababaxse");
    std::cout << manacher.palindromic_string() << std::endl;
    return 0;
}