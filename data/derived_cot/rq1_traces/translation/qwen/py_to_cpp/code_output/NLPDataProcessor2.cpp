#include <vector>
#include <string>
#include <map>
#include <regex>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <utility>

class NLPDataProcessor2 {
public:
    std::vector<std::vector<std::string>> process_data(const std::vector<std::string>& string_list) {
        std::vector<std::vector<std::string>> words_list;
        for (const auto& str : string_list) {
            std::regex pattern("[^a-zA-Z\\s]");
            std::string processed_str = std::regex_replace(str, pattern, "");
            std::transform(processed_str.begin(), processed_str.end(), processed_str.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            std::istringstream iss(processed_str);
            std::vector<std::string> words;
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
            words_list.push_back(words);
        }
        return words_list;
    }

    std::map<std::string, int> calculate_word_frequency(const std::vector<std::vector<std::string>>& words_list) {
        std::map<std::string, int> word_count;
        for (const auto& words : words_list) {
            for (const auto& word : words) {
                ++word_count[word];
            }
        }
        std::vector<std::pair<std::string, int>> sorted;
        for (const auto& kv : word_count) {
            sorted.push_back(kv);
        }
        std::sort(sorted.begin(), sorted.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
        std::map<std::string, int> top_5;
        for (int i = 0; i < std::min(5, (int)sorted.size()); ++i) {
            top_5[sorted[i].first] = sorted[i].second;
        }
        return top_5;
    }

    std::map<std::string, int> process(const std::vector<std::string>& string_list) {
        auto words_list = process_data(string_list);
        return calculate_word_frequency(words_list);
    }
};