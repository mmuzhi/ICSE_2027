#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include <utility>

class NLPDataProcessor2 {
public:
    std::vector<std::vector<std::string>> process_data(const std::vector<std::string>& string_list) {
        std::vector<std::vector<std::string>> words_list;
        std::regex pattern("[^a-zA-Z\\s]");
        
        for (const std::string& str : string_list) {
            std::string lower_str = str;
            std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            
            std::string processed_string = std::regex_replace(lower_str, pattern, "");
            
            std::istringstream iss(processed_string);
            std::vector<std::string> words;
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
            words_list.push_back(words);
        }
        return words_list;
    }

    std::vector<std::pair<std::string, int>> calculate_word_frequency(const std::vector<std::vector<std::string>>& words_list) {
        std::unordered_map<std::string, int> word_frequency;
        for (const std::vector<std::string>& words : words_list) {
            for (const std::string& word : words) {
                word_frequency[word]++;
            }
        }
        
        std::vector<std::pair<std::string, int>> sorted_word_frequency(word_frequency.begin(), word_frequency.end());
        std::sort(sorted_word_frequency.begin(), sorted_word_frequency.end(),
                  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                      return a.second > b.second;
                  });
        
        if (sorted_word_frequency.size() > 5) {
            sorted_word_frequency.resize(5);
        }
        
        return sorted_word_frequency;
    }

    std::vector<std::pair<std::string, int>> process(const std::vector<std::string>& string_list) {
        std::vector<std::vector<std::string>> words_list = process_data(string_list);
        return calculate_word_frequency(words_list);
    }
};