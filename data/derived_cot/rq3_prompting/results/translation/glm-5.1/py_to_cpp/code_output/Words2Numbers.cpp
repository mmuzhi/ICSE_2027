#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

class Words2Numbers {
public:
    Words2Numbers() {
        units = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
            "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
            "sixteen", "seventeen", "eighteen", "nineteen"
        };
        tens = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
        scales = {"hundred", "thousand", "million", "billion", "trillion"};

        numwords["and"] = {1, 0};
        for (int idx = 0; idx < (int)units.size(); idx++) {
            numwords[units[idx]] = {1, idx};
        }
        for (int idx = 0; idx < (int)tens.size(); idx++) {
            numwords[tens[idx]] = {1, idx * 10};
        }
        for (int idx = 0; idx < (int)scales.size(); idx++) {
            long long exponent = (idx * 3 != 0) ? (idx * 3) : 2;
            long long val = 1;
            for (int i = 0; i < exponent; i++) val *= 10;
            numwords[scales[idx]] = {val, 0};
        }

        ordinal_words = {{"first", 1}, {"second", 2}, {"third", 3}, {"fifth", 5}, {"eighth", 8}, {"ninth", 9}, {"twelfth", 12}};
        ordinal_endings = {{"ieth", "y"}, {"th", ""}};
    }

    std::string text2int(const std::string& textnum) {
        std::string textnum_copy = textnum;
        std::replace(textnum_copy.begin(), textnum_copy.end(), '-', ' ');

        long long current = 0, result = 0;
        std::string curstring;
        bool onnumber = false;

        std::istringstream iss(textnum_copy);
        std::string word;
        while (iss >> word) {
            if (ordinal_words.count(word)) {
                long long scale = 1;
                long long increment = ordinal_words[word];
                current = current * scale + increment;
                onnumber = true;
            } else {
                for (auto& [ending, replacement] : ordinal_endings) {
                    if (word.size() >= ending.size() &&
                        word.substr(word.size() - ending.size()) == ending) {
                        word = word.substr(0, word.size() - ending.size()) + replacement;
                    }
                }

                if (numwords.find(word) == numwords.end()) {
                    if (onnumber) {
                        curstring += std::to_string(result + current) + " ";
                    }
                    curstring += word + " ";
                    result = current = 0;
                    onnumber = false;
                } else {
                    long long scale = numwords[word].first;
                    long long increment = numwords[word].second;
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
        std::string textnum_copy = textnum;
        std::replace(textnum_copy.begin(), textnum_copy.end(), '-', ' ');

        std::istringstream iss(textnum_copy);
        std::string word;
        while (iss >> word) {
            if (ordinal_words.count(word)) {
                continue;
            } else {
                for (auto& [ending, replacement] : ordinal_endings) {
                    if (word.size() >= ending.size() &&
                        word.substr(word.size() - ending.size()) == ending) {
                        word = word.substr(0, word.size() - ending.size()) + replacement;
                    }
                }

                if (numwords.find(word) == numwords.end()) {
                    return false;
                }
            }
        }

        return true;
    }

private:
    std::unordered_map<std::string, std::pair<long long, long long>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::unordered_map<std::string, int> ordinal_words;
    std::vector<std::pair<std::string, std::string>> ordinal_endings;
};