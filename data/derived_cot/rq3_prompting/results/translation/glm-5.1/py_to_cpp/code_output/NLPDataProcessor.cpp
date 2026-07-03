#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class NLPDataProcessor {
public:
    std::vector<std::string> construct_stop_word_list() {
        return {"a", "an", "the"};
    }

    std::vector<std::vector<std::string>> remove_stop_words(const std::vector<std::string>& string_list, const std::vector<std::string>& stop_word_list) {
        std::vector<std::vector<std::string>> answer;
        for (const std::string& str : string_list) {
            std::vector<std::string> string_split;
            std::istringstream iss(str);
            std::string word;
            while (iss >> word) {
                string_split.push_back(word);
            }

            // Replicating the exact behavior of Python's `for word in string_split:`
            // which skips the next element if the current element is removed in-place.
            for (size_t i = 0; i < string_split.size(); ++i) {
                const std::string& w = string_split[i];
                if (std::find(stop_word_list.begin(), stop_word_list.end(), w) != stop_word_list.end()) {
                    string_split.erase(string_split.begin() + i);
                    // We intentionally do NOT decrement `i` here.
                    // When an element is erased, the next element shifts into index `i`.
                    // The loop's `++i` will then skip over this shifted element,
                    // perfectly matching Python's iterator behavior over a mutating list.
                }
            }
            answer.push_back(string_split);
        }
        return answer;
    }

    std::vector<std::vector<std::string>> process(const std::vector<std::string>& string_list) {
        std::vector<std::string> stop_word_list = construct_stop_word_list();
        return remove_stop_words(string_list, stop_word_list);
    }
};