#include <string>
#include <stdexcept>

class Manacher {
private:
    std::string input_string;

public:
    Manacher(std::string input_string) : input_string(std::move(input_string)) {}

    int palindromic_length(int center, int diff, const std::string& string) {
        if (center - diff == -1 || 
            center + diff == static_cast<int>(string.size()) || 
            string[center - diff] != string[center + diff]) {
            return 0;
        }
        return 1 + palindromic_length(center, diff + 1, string);
    }

    std::string palindromic_string() {
        int max_length = 0;

        std::string new_input_string;
        std::string output_string;

        // Replicating Python's IndexError for empty string when accessing input_string[-1]
        if (input_string.empty()) {
            throw std::out_of_range("input_string is empty");
        }

        for (int i = 0; i < static_cast<int>(input_string.size()) - 1; ++i) {
            new_input_string += input_string[i];
            new_input_string += "|";
        }
        new_input_string += input_string.back();

        int start = -1; // Using -1 to detect unassigned state to mimic Python's UnboundLocalError

        for (int i = 0; i < static_cast<int>(new_input_string.size()); ++i) {
            int length = palindromic_length(i, 1, new_input_string);

            if (max_length < length) {
                max_length = length;
                start = i;
            }
        }

        // If start was never assigned, it means max_length remained 0.
        // In Python, this leads to an UnboundLocalError when evaluating the slice.
        if (start == -1) {
            throw std::runtime_error("local variable 'start' referenced before assignment");
        }

        for (int i = start - max_length; i <= start + max_length; ++i) {
            if (new_input_string[i] != '|') {
                output_string += new_input_string[i];
            }
        }

        return output_string;
    }
};