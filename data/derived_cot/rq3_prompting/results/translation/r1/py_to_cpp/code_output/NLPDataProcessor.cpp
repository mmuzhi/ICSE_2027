#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>

class NLPDataProcessor {
public:
    std::vector<std::string> construct_stop_word_list() {
        return {"a", "an", "the"};
    }

    std::vector<std::vector<std::string>> remove_stop_words(
        const std::vector<std::string>& string_list,
        const std::vector<std::string>& stop_word_list) {

        // Build a set for O(1) lookup
        std::unordered_set<std::string> stop_set(stop_word_list.begin(), stop_word_list.end());

        std::vector<std::vector<std::string>> result;
        result.reserve(string_list.size());

        for (const std::string& s : string_list) {
            // Split by whitespace (same as Python's split())
            std::istringstream iss(s);
            std::vector<std::string> words;
            std::string w;
            while (iss >> w) {
                words.push_back(w);
            }

            // Remove stop words in the same way as Python:
            // iterate over the list and remove first occurrence when encounter a stop word.
            for (size_t i = 0; i < words.size(); ) {
                const std::string& current = words[i];
                if (stop_set.find(current) != stop_set.end()) {
                    // Remove first occurrence of this value (exactly like list.remove)
                    auto it = std::find(words.begin(), words.end(), current);
                    words.erase(it);
                    // Do not increment i because next element shifts to i
                } else {
                    ++i;
                }
            }
            result.push_back(std::move(words));
        }
        return result;
    }

    std::vector<std::vector<std::string>> process(const std::vector<std::string>& string_list) {
        std::vector<std::string> stop_words = construct_stop_word_list();
        return remove_stop_words(string_list, stop_words);
    }
};