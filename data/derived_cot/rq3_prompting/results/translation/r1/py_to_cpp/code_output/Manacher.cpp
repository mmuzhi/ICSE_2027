#include <string>
#include <stdexcept>

class Manacher {
private:
    std::string input_string;

public:
    Manacher(const std::string& input_string) : input_string(input_string) {}

    int palindromic_length(int center, int diff, const std::string& string) {
        if (center - diff == -1 ||
            center + diff == static_cast<int>(string.length()) ||
            string[center - diff] != string[center + diff]) {
            return 0;
        }
        return 1 + palindromic_length(center, diff + 1, string);
    }

    std::string palindromic_string() {
        if (input_string.empty()) {
            throw std::out_of_range("Empty string");
        }

        int n = static_cast<int>(input_string.length());
        std::string new_input_string;

        // Insert '|' between characters (like Python)
        for (int i = 0; i < n - 1; ++i) {
            new_input_string.push_back(input_string[i]);
            new_input_string.push_back('|');
        }
        new_input_string.push_back(input_string.back());

        int max_length = 0;
        int start; // intentionally uninitialized (mirrors Python's NameError if never set)

        int len = static_cast<int>(new_input_string.length());
        for (int i = 0; i < len; ++i) {
            int length = palindromic_length(i, 1, new_input_string);
            if (max_length < length) {
                max_length = length;
                start = i;
            }
        }

        std::string output_string;
        for (int j = start - max_length; j <= start + max_length; ++j) {
            if (new_input_string[j] != '|') {
                output_string.push_back(new_input_string[j]);
            }
        }

        return output_string;
    }
};