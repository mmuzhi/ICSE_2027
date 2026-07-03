#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <locale>
#include <sstream>
#include <functional>

class NLPDataProcessor2 {
public:
    std::vector<std::vector<std::string>> process_data(const std::vector<std::string>& string_list) {
        std::vector<std::vector<std::string>> words_list;
        for (const auto& str : string_list) {
            std::string processed = std::regex_replace(str, std::regex(R"([^a-zA-Z\s])"), "");
            std::transform(processed.begin(), processed.end(), processed.begin(),
                [&](unsigned char c) { return std::tolower(c, std::locale::classic()); });
            std::istringstream iss(processed);
            std::vector<std::string> words;
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
            words_list.push_back(words);
        }
        return words_list;
    }

    std::unordered_map<std::string, int> calculate_word_frequency(const std::vector<std::vector<std::string>>& words_list) {
        std::unordered_map<std::string, int> word_count;
        for (const auto& words : words_list) {
            for (const auto& word : words) {
                word_count[word]++;
            }
        }

        std::vector<std::pair<int, std::string>> temp;
        for (const auto& kv : word_count) {
            temp.push_back(std::make_pair(kv.second, kv.first));
        }

        std::sort(temp.begin(), temp.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        std::unordered_map<std::string, int> top_5;
        for (size_t i = 0; i < std::min(5, temp.size()); ++i) {
            top_5[temp[i].second] = temp[i].first;
        }
        return top_5;
    }

    std::unordered_map<std::string, int> process(const std::vector<std::string>& string_list) {
        auto words_list = process_data(string_list);
        return calculate_word_frequency(words_list);
    }
};