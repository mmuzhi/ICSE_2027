#include <string>
#include <stdexcept>

class Manacher {
private:
    std::string input_string;

public:
    Manacher(const std::string& s) : input_string(s) {}

    int palindromic_length(int center, int diff, const std::string& s) {
        int count = 0;
        int left = center - diff;
        int right = center + diff;
        while (left >= 0 && right < static_cast<int>(s.size()) && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
        return count;
    }

    std::string palindromic_string() {
        if (input_string.empty()) {
            throw std::out_of_range("string index out of range");
        }

        std::string new_input_string;
        size_t n = input_string.size();
        for (size_t i = 0; i < n - 1; i++) {
            new_input_string += input_string[i];
            new_input_string += '|';
        }
        new_input_string += input_string.back();

        int max_length = 0;
        int start_index = 0;

        int len = static_cast<int>(new_input_string.size());
        for (int i = 0; i < len; i++) {
            int length = palindromic_length(i, 1, new_input_string);
            if (length > max_length) {
                max_length = length;
                start_index = i;
            }
        }

        int start = start_index - max_length;
        int end = start_index + max_length;
        std::string result;
        for (int i = start; i <= end; i++) {
            if (new_input_string[i] != '|') {
                result += new_input_string[i];
            }
        }
        return result;
    }
};