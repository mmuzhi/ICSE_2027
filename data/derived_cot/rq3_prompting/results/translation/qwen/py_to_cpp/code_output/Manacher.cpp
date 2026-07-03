#include <string>
#include <vector>

class Manacher {
public:
    Manacher(const std::string& input_string) : input_string(input_string) {}

    std::string palindromic_string();

private:
    int palindromic_length(int center, int diff, const std::string& s) {
        if (center - diff < 0 || center + diff >= s.length()) {
            return 0;
        }
        if (s[center-diff] != s[center+diff]) {
            return 0;
        }
        return 1 + palindromic_length(center, diff+1, s);
    }

    std::string input_string;
};

std::string Manacher::palindromic_string() {
    if (input_string.empty()) {
        return "";
    }
    if (input_string.length() == 1) {
        return input_string;
    }

    std::string new_input_string;
    for (int i = 0; i < input_string.length() - 1; i++) {
        new_input_string += input_string[i];
        new_input_string += '|';
    }
    new_input_string += input_string.back();

    int max_length = 0;
    int start = 0;

    for (int i = 0; i < new_input_string.length(); i++) {
        int length = palindromic_length(i, 1, new_input_string);
        if (max_length < length) {
            max_length = length;
            start = i;
        }
    }

    std::string substring = new_input_string.substr(start - max_length, 2*max_length+1);
    std::string output_string;
    for (char c : substring) {
        if (c != '|') {
            output_string += c;
        }
    }
    return output_string;
}