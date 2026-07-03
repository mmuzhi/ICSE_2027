#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include <regex>
#include <sstream>
#include <utility>

class NLPDataProcessor2 {
public:
    std::vector<std::vector<std::string>> process_data(const std::vector<std::string>& string_list) {
        std::vector<std::vector<std::string>> words_list;
        for (const auto& str : string_list) {
            std::string lower_string = str;
            std::transform(lower_string.begin(), lower_string.end(), lower_string.begin(),
                [](unsigned char c) { return std::tolower(c); });
            std::regex pattern("[^a-z\\s]");
            std::string processed_string = std::regex_replace(lower_string, pattern, "");
            std::vector<std::string> words;
            std::istringstream iss(processed_string);
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
            words_list.push_back(words);
        }
        return words_list;
    }

    std::vector<std::pair<std::string, int>> calculate_word_frequency(const std::vector<std::vector<std::string>>& words_list) {
        std::unordered_map<std::string, int> freqMap;
        std::vector<std::string> order;
        for (const auto& words : words_list) {
            for (const auto& word : words) {
                if (freqMap.find(word) == freqMap.end()) {
                    freqMap[word] = 1;
                    order.push_back(word);
                } else {
                    freqMap[word]++;
                }
            }
        }
        std::vector<std::pair<std::string, int>> items;
        for (const auto& w : order) {
            items.push_back(std::make_pair(w, freqMap[w]));
        }
        std::stable_sort(items.begin(), items.end(),
            [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second > b.second;
            });
        if (items.size() > 5) {
            items.resize(5);
        }
        return items;
    }

    std::vector<std::pair<std::string, int>> process(const std::vector<std::string>& string_list) {
        auto words_list = process_data(string_list);
        return calculate_word_frequency(words_list);
    }
};