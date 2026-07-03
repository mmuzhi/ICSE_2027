#include <iostream>
#include <string>

class Manacher {
private:
    std::string inputString;

public:
    Manacher(const std::string& input) : inputString(input) {}

    std::string preprocess() {
        std::string processed;
        processed += '|';
        for (char c : inputString) {
            processed += '|';
            processed += c;
        }
        processed += '|';
        return processed;
    }

    int palindromic_length(const std::string& s, int center) {
        int diff = 1;
        while (center - diff >= 0 && center + diff < s.length() && s[center - diff] == s[center + diff]) {
            diff++;
        }
        return diff - 1;
    }

    std::string palindromic_string() {
        std::string processedString = preprocess();
        int maxLength = 0;
        int centerIndex = 0;

        for (int i = 0; i < processedString.length(); i++) {
            int length = palindromic_length(processedString, i);
            if (length > maxLength) {
                maxLength = length;
                centerIndex = i;
            }
        }

        std::string result = processedString.substr(centerIndex - maxLength, 2 * maxLength + 1);
        std::string clean;
        for (char c : result) {
            if (c != '|') {
                clean += c;
            }
        }
        return clean;
    }
};

int main() {
    Manacher manacher("ababaxse");
    std::cout << manacher.palindromic_string() << std::endl;
    return 0;
}