#include <vector>
#include <string>
#include <sstream>

class NLPDataProcessor {
public:
    static std::vector<std::string> construct_stop_word_list();
    static std::vector<std::vector<std::string>> remove_stop_words(const std::vector<std::string>& string_list, const std::vector<std::string>& stop_word_list);
    static std::vector<std::vector<std::string>> process(const std::vector<std::string>& string_list);
};

std::vector<std::string> NLPDataProcessor::construct_stop_word_list() {
    return {"a", "an", "the"};
}

std::vector<std::vector<std::string>> NLPDataProcessor::remove_stop_words(const std::vector<std::string>& string_list, const std::vector<std::string>& stop_word_list) {
    std::vector<std::vector<std::string>> result;
    for (const auto& str : string_list) {
        std::istringstream iss(str);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }
        std::vector<std::string> filtered;
        for (const auto& w : words) {
            bool is_stop = false;
            for (const auto& sw : stop_word_list) {
                if (w == sw) {
                    is_stop = true;
                    break;
                }
            }
            if (!is_stop) {
                filtered.push_back(w);
            }
        }
        result.push_back(filtered);
    }
    return result;
}

std::vector<std::vector<std::string>> NLPDataProcessor::process(const std::vector<std::string>& string_list) {
    auto stop_word_list = NLPDataProcessor::construct_stop_word_list();
    return NLPDataProcessor::remove_stop_words(string_list, stop_word_list);
}