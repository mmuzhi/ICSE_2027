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
        std::vector<std::vector<std::string>> result;
        for (const auto& s : string_list) {
            std::istringstream iss(s);
            std::vector<std::string> split;
            std::string word;
            while (iss >> word) {
                split.push_back(word);
            }
            std::vector<std::string> filtered;
            for (const auto& w : split) {
                if (std::find(stop_word_list.begin(), stop_word_list.end(), w) == stop_word_list.end()) {
                    filtered.push_back(w);
                }
            }
            result.push_back(filtered);
        }
        return result;
    }

    std::vector<std::vector<std::string>> process(const std::vector<std::string>& string_list) {
        auto stop_word_list = construct_stop_word_list();
        return remove_stop_words(string_list, stop_word_list);
    }
};