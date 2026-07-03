#include <string>

class Manacher {
private:
    std::string input_string;

public:
    Manacher(const std::string& s) : input_string(s) {}

    int palindromic_length(int center, int diff, const std::string& str) {
        int left = center - diff;
        int right = center + diff;
        if (left < 0 || right >= static_cast<int>(str.length()) || str[left] != str[right]) {
            return 0;
        }
        return 1 + palindromic_length(center, diff + 1, str);
    }

    std::string palindromic_string() {
        if (input_string.empty()) {
            return "";
        }

        std::string transformed;
        for (size_t i = 0; i < input_string.length() - 1; ++i) {
            transformed += input_string[i];
            transformed += '|';
        }
        transformed += input_string.back();

        int max_length = 0;
        int best_center = 0;

        for (size_t i = 0; i < transformed.length(); ++i) {
            int length = palindromic_length(i, 1, transformed);
            if (length > max_length) {
                max_length = length;
                best_center = i;
            }
        }

        std::string result;
        for (int i = best_center - max_length; i <= best_center + max_length; ++i) {
            if (transformed[i] != '|') {
                result += transformed[i];
            }
        }

        return result;
    }
};