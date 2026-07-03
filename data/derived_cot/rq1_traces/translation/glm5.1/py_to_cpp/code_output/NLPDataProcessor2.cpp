#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <utility>

class NLPDataProcessor2 {
public:
    std::vector<std::vector<std::string>> process_data(const std::vector<std::string>& string_list) {
        std::vector<std::vector<std::string>> words_list;
        for (const auto& str : string_list) {
            std::string processed_string;
            for (char c : str) {
                int lower_c = std::tolower(static_cast<unsigned char>(c));
                // Keep only English letters and spaces
                bool is_alpha = (lower_c >= 'a' && lower_c <= 'z');
                bool is_space = std::isspace(lower_c) != 0;
                if (is_alpha || is_space) {
                    processed_string += static_cast<char>(lower_c);
                }
            }
            
            // Split the string into words
            std::vector<std::string> words;
            std::string word;
            for (char c : processed_string) {
                if (std::isspace(static_cast<unsigned char>(c))) {
                    if (!word.empty()) {
                        words.push_back(word);
                        word.clear();
                    }
                } else {
                    word += c;
                }
            }
            if (!word.empty()) {
                words.push_back(word);
            }
            words_list.push_back(words);
        }
        return words_list;
    }

    // Using std::vector<std::pair<std::string, int>> to represent an ordered dictionary,
    // which preserves the insertion/sorted order unlike std::map.
    std::vector<std::pair<std::string, int>> calculate_word_frequency(const std::vector<std::vector<std::string>>& words_list) {
        std::vector<std::pair<std::string, int>> word_frequency_vec;
        std::unordered_map<std::string, size_t> word_index;
        
        for (const auto& words : words_list) {
            for (const auto& word : words) {
                auto it = word_index.find(word);
                if (it != word_index.end()) {
                    word_frequency_vec[it->second].second++;
                } else {
                    word_index[word] = word_frequency_vec.size();
                    word_frequency_vec.emplace_back(word, 1);
                }
            }
        }
        
        // Sort by frequency in descending order. 
        // std::stable_sort preserves the original insertion order for ties, matching Python 3.7+ dict behavior.
        std::stable_sort(word_frequency_vec.begin(), word_frequency_vec.end(), 
            [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second > b.second;
            });
            
        size_t top_n = std::min(word_frequency_vec.size(), static_cast<size_t>(5));
        std::vector<std::pair<std::string, int>> top_5_word_frequency(word_frequency_vec.begin(), word_frequency_vec.begin() + top_n);
        return top_5_word_frequency;
    }

    std::vector<std::pair<std::string, int>> process(const std::vector<std::string>& string_list) {
        auto words_list = process_data(string_list);
        return calculate_word_frequency(words_list);
    }
};