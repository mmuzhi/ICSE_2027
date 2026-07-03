#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>

class Words2Numbers {
    std::map<std::string, std::pair<long long, long long>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::map<std::string, long long> ordinal_words;
    std::vector<std::pair<std::string, std::string>> ordinal_endings;

public:
    Words2Numbers() {
        units = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
        tens = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
        scales = {"hundred", "thousand", "million", "billion", "trillion"};
        ordinal_words = {{"first", 1}, {"second", 2}, {"third", 3}, {"fifth", 5}, {"eighth", 8}, {"ninth", 9}, {"twelfth", 12}};
        ordinal_endings = {{"ieth", "y"}, {"th", ""}};

        numwords["and"] = std::make_pair(1, 0);
        for (int idx = 0; idx < units.size(); idx++) {
            numwords[units[idx]] = std::make_pair(1, idx);
        }
        for (int idx = 2; idx < tens.size(); idx++) {
            numwords[tens[idx]] = std::make_pair(1, idx * 10);
        }
        for (int idx = 0; idx < scales.size(); idx++) {
            long long scale_value = (idx == 0) ? 100 : 1LL * (1000) * (1LL * (1000) * (1000LL)) * (idx / 3);
            numwords[scales[idx]] = std::make_pair(scale_value, 0);
        }
    }

    std::string text2int(const std::string& textnum) {
        std::string corrected;
        for (char c : textnum) {
            if (c == '-') corrected += ' ';
            else corrected += c;
        }

        std::istringstream iss(corrected);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        long long current = 0;
        long long result = 0;
        std::string curstring;
        bool onnumber = false;

        for (const std::string& w : words) {
            auto ordinal_it = ordinal_words.find(w);
            if (ordinal_it != ordinal_words.end()) {
                long long scale = 1;
                long long increment = ordinal_it->second;
                current = current * scale + increment;
                onnumber = true;
            } else {
                bool changed = false;
                for (const auto& ending : ordinal_endings) {
                    if (w.size() > ending.first.size() && 
                        w.substr(w.size() - ending.first.size()) == ending.first) {
                        std::string new_word = w.substr(0, w.size() - ending.first.size()) + ending.second;
                        w = new_word;
                        changed = true;
                    }
                }

                if (numwords.find(w) != numwords.end()) {
                    long long scale = numwords[w].first;
                    long long increment = numwords[w].second;
                    current = current * scale + increment;
                    if (scale > 100) {
                        result += current;
                        current = 0;
                    }
                    onnumber = true;
                } else {
                    if (onnumber) {
                        curstring += std::to_string(result + current) + " ";
                    }
                    curstring += w + " ";
                    result = current = 0;
                    onnumber = false;
                }
            }
        }

        if (onnumber) {
            curstring += std::to_string(result + current);
        }

        return curstring;
    }

    bool is_valid_input(const std::string& textnum) {
        std::string corrected;
        for (char c : textnum) {
            if (c == '-') corrected += ' ';
            else corrected += c;
        }

        std::istringstream iss(corrected);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        for (const std::string& w : words) {
            bool valid = false;
            auto ordinal_it = ordinal_words.find(w);
            if (ordinal_it != ordinal_words.end()) {
                continue;
            }

            bool changed = false;
            for (const auto& ending : ordinal_endings) {
                if (w.size() > ending.first.size() && 
                    w.substr(w.size() - ending.first.size()) == ending.first) {
                    std::string new_word = w.substr(0, w.size() - ending.first.size()) + ending.second;
                    w = new_word;
                    changed = true;
                }
            }

            if (numwords.find(w) != numwords.end()) {
                valid = true;
            } else {
                return false;
            }
        }

        return true;
    }
};