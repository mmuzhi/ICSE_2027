#include <iostream>
#include <string>
#include <algorithm>

class Manacher {
private:
    std::string inputString;

    std::string preprocess(const std::string& s) {
        std::string sb;
        sb.reserve(s.length() * 2 + 1);
        for (size_t i = 0; i < s.length(); i++) {
            sb += '|';
            sb += s[i];
        }
        sb += '|';
        return sb;
    }

protected:
    int palindromicLength(const std::string& s, int center) {
        int diff = 1;
        while (center - diff >= 0 && center + diff < static_cast<int>(s.length()) && s[center - diff] == s[center + diff]) {
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

        for (int i = 0; i < static_cast<int>(processedString.length()); i++) {
            int length = palindromicLength(processedString, i);
            if (length > maxLength) {
                maxLength = length;
                centerIndex = i;
            }
        }

        // Java's substring(start, end) translates to C++'s substr(start, count)
        std::string result = processedString.substr(centerIndex - maxLength, maxLength * 2 + 1);
        
        // Erase-remove idiom to match Java's replace("|", "")
        result.erase(std::remove(result.begin(), result.end(), '|'), result.end());
        
        return result;
    }
};

int main() {
    Manacher manacher("ababaxse");
    std::cout << manacher.palindromicString() << std::endl;
    return 0;
}