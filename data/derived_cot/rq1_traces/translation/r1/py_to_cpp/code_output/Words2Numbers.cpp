#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

class Words2Numbers {
private:
    std::unordered_map<std::string, std::pair<long long, long long>> numwords;
    std::unordered_map<std::string, long long> ordinal_words;
    std::vector<std::pair<std::string, std::string>> ordinal_endings;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;

public:
    Words2Numbers() {
        units = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
            "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
            "sixteen", "seventeen", "eighteen", "nineteen"
        };
        tens = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
        scales = {"hundred", "thousand", "million", "billion", "trillion"};

        numwords["and"] = std::make_pair(1, 0);
        for (int idx = 0; idx < units.size(); idx++) {
            numwords[units[idx]] = std::make_pair(1, idx);
        }
        for (int idx = 0; idx < tens.size(); idx++) {
            if (!tens[idx].empty()) {
                numwords[tens[idx]] = std::make_pair(1, idx * 10);
            }
        }
        std::vector<long long> scale_values = {100, 1000, 1000000, 1000000000, 1000000000000LL};
        for (int idx = 0; idx < scales.size(); idx++) {
            numwords[scales[idx]] = std::make_pair(scale_values[idx], 0);
        }

        ordinal_words = {
            {"first", 1},
            {"second", 2},
            {"third", 3},
            {"fifth", 5},
            {"eighth", 8},
            {"ninth", 9},
            {"twelfth", 12}
        };

        ordinal_endings = {
            {"ieth", "y"},
            {"th", ""}
        };
    }

    std::string text2int(const std::string& textnum) {
        std::string processed = textnum;
        std::replace(processed.begin(), processed.end(), '-', ' ');
        std::istringstream iss(processed);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        long long current = 0;
        long long result = 0;
        std::string curstring;
        bool onnumber = false;

        for (const auto& w : words) {
            auto it_ordinal = ordinal_words.find(w);
            if (it_ordinal != ordinal_words.end()) {
                long long increment = it_ordinal->second;
                current = current * 1 + increment;
                onnumber = true;
            } else {
                std::string modified_word = w;
                bool found_ending = false;
                for (const auto& ending_pair : ordinal_endings) {
                    const std::string& ending = ending_pair.first;
                    const std::string& replacement = ending_pair.second;
                    if (w.size() >= ending.size() && w.substr(w.size() - ending.size()) == ending) {
                        modified_word = w.substr(0, w.size() - ending.size()) + replacement;
                        found_ending = true;
                        break;
                    }
                }

                auto it_num = numwords.find(modified_word);
                if (it_num == numwords.end()) {
                    if (onnumber) {
                        curstring += std::to_string(result + current) + " ";
                        result = 0;
                        current = 0;
                        onnumber = false;
                    }
                    curstring += w + " ";
                } else {
                    long long scale = it_num->second.first;
                    long long increment = it_num->second.second;
                    current = current * scale + increment;
                    if (scale > 100) {
                        result += current;
                        current = 0;
                    }
                    onnumber = true;
                }
            }
        }

        if (onnumber) {
            curstring += std::to_string(result + current);
        }

        return curstring;
    }

    bool is_valid_input(const std::string& textnum) {
        std::string processed = textnum;
        std::replace(processed.begin(), processed.end(), '-', ' ');
        std::istringstream iss(processed);
        std::string word;

        while (iss >> word) {
            if (ordinal_words.find(word) != ordinal_words.end()) {
                continue;
            }

            bool found_ending = false;
            std::string modified_word = word;
            for (const auto& ending_pair : ordinal_endings) {
                const std::string& ending = ending_pair.first;
                const std::string& replacement = ending_pair.second;
                if (word.size() >= ending.size() && word.substr(word.size() - ending.size()) == ending) {
                    modified_word = word.substr(0, word.size() - ending.size()) + replacement;
                    found_ending = true;
                    break;
                }
            }

            if (numwords.find(modified_word) == numwords.end()) {
                return false;
            }
        }
        return true;
    }
};