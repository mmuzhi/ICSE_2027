#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class NLPDataProcessor {
public:
    std::vector<std::string> construct_stop_word_list() {
        return {"a", "an", "the"};
    }

    std::vector<std::vector<std::string>> remove_stop_words(
        const std::vector<std::string>& string_list,
        const std::vector<std::string>& stop_word_list) {
        
        std::vector<std::vector<std::string>> answer;
        for (const std::string& str : string_list) {
            std::vector<std::string> string_split = split(str);
            
            // Note: The original Python code modifies `string_split` while iterating over it,
            // which causes it to skip elements. To keep behavior identical, this C++ code
            // replicates that exact logic by incrementing the index regardless of whether
            // an element is removed, and using `std::find` to mimic `list.remove()` which
            // removes the first occurrence.
            for (size_t i = 0; i < string_split.size(); ) {
                std::string word = string_split[i];
                if (std::find(stop_word_list.begin(), stop_word_list.end(), word) != stop_word_list.end()) {
                    auto it = std::find(string_split.begin(), string_split.end(), word);
                    string_split.erase(it);
                    i++; // Mimics Python's internal index increment after removal
                } else {
                    i++;
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

private:
    // Helper function to replicate Python's str.split() behavior
    std::vector<std::string> split(const std::string& s) {
        std::vector<std::string> words;
        std::istringstream iss(s);
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }
        return words;
    }
};