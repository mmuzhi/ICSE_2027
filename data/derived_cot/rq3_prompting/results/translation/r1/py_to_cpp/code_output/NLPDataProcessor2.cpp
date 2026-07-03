#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <cctype>

class NLPDataProcessor2 {
public:
    // Keep only English letters and spaces, convert to lowercase, split into words.
    std::vector<std::vector<std::string>> process_data(const std::vector<std::string>& string_list) {
        std::vector<std::vector<std::string>> words_list;
        std::regex non_alpha_space("[^a-zA-Z\\s]");
        for (const auto& s : string_list) {
            // Remove non-letters/spaces, then lowercase
            std::string cleaned = std::regex_replace(s, non_alpha_space, "");
            std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
            // Split into words
            std::vector<std::string> words;
            std::istringstream iss(cleaned);
            std::string word;
            while (iss >> word) {
                words.push_back(word);
            }
            words_list.push_back(std::move(words));
        }
        return words_list;
    }

    // Calculate word frequency from list of word-lists, return top 5 in descending frequency order.
    // Tie-breaking: words that appear first in the input keep their relative order.
    std::vector<std::pair<std::string, int>> calculate_word_frequency(
        const std::vector<std::vector<std::string>>& words_list) {
        std::unordered_map<std::string, int> freq;
        std::vector<std::string> order; // first occurrence order
        for (const auto& word_list : words_list) {
            for (const auto& w : word_list) {
                if (freq.find(w) == freq.end()) {
                    order.push_back(w);
                }
                freq[w]++;
            }
        }

        // Build vector of pairs for sorting
        std::vector<std::pair<std::string, int>> freq_vec;
        freq_vec.reserve(order.size());
        for (const auto& word : order) {
            freq_vec.emplace_back(word, freq[word]);
        }

        // Sort by frequency descending, then by original order (stable relative to first occurrence)
        std::sort(freq_vec.begin(), freq_vec.end(),
                  [](const auto& a, const auto& b) {
                      if (a.second != b.second)
                          return a.second > b.second;
                      // For equal freq, keep original order (already in 'order' order)
                      return false; // false means a not less than b, so stable sort maintains order
                  });

        // Take top 5
        const size_t top = std::min<size_t>(5, freq_vec.size());
        return std::vector<std::pair<std::string, int>>(freq_vec.begin(), freq_vec.begin() + top);
    }

    // Combined processing: process_data + calculate_word_frequency.
    std::vector<std::pair<std::string, int>> process(const std::vector<std::string>& string_list) {
        auto words_list = process_data(string_list);
        return calculate_word_frequency(words_list);
    }
};