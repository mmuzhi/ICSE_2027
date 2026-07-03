#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

class Words2Numbers {
private:
    std::unordered_map<std::string, std::pair<long long, long long>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::unordered_map<std::string, long long> ordinal_words;
    std::vector<std::pair<std::string, std::string>> ordinal_endings;

    static long long pow10(int exp) {
        long long r = 1;
        for (int i = 0; i < exp; ++i) r *= 10;
        return r;
    }

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
        for (size_t idx = 0; idx < units.size(); ++idx) {
            numwords[units[idx]] = {1, static_cast<long long>(idx)};
        }
        for (size_t idx = 0; idx < tens.size(); ++idx) {
            numwords[tens[idx]] = {1, static_cast<long long>(idx) * 10};
        }
        for (size_t idx = 0; idx < scales.size(); ++idx) {
            // idx*3 or 2 : if idx==0 then use 2, else idx*3
            int exp = (idx == 0) ? 2 : static_cast<int>(idx) * 3;
            numwords[scales[idx]] = {pow10(exp), 0};
        }

        ordinal_words = {{"first", 1}, {"second", 2}, {"third", 3}, {"fifth", 5},
                         {"eighth", 8}, {"ninth", 9}, {"twelfth", 12}};
        ordinal_endings = {{"ieth", "y"}, {"th", ""}};
    }

    std::string text2int(const std::string& textnum) {
        std::string input = textnum;
        std::replace(input.begin(), input.end(), '-', ' ');

        std::istringstream iss(input);
        std::string word;
        long long current = 0, result = 0;
        std::string curstring;
        bool onnumber = false;

        while (iss >> word) {
            // Check if word is in ordinal_words directly
            auto ord_it = ordinal_words.find(word);
            if (ord_it != ordinal_words.end()) {
                long long increment = ord_it->second;
                current = current * 1 + increment;  // scale = 1
                onnumber = true;
                continue;
            }

            // Try ordinal endings removal
            std::string modified = word;
            for (const auto& ending_pair : ordinal_endings) {
                const std::string& ending = ending_pair.first;
                const std::string& replacement = ending_pair.second;
                if (modified.length() >= ending.length() &&
                    modified.compare(modified.length() - ending.length(), ending.length(), ending) == 0) {
                    modified = modified.substr(0, modified.length() - ending.length()) + replacement;
                }
            }

            auto it = numwords.find(modified);
            if (it == numwords.end()) {
                // Unknown word
                if (onnumber) {
                    curstring += std::to_string(result + current) + " ";
                }
                curstring += word + " ";  // original word (before modification)
                result = 0;
                current = 0;
                onnumber = false;
            } else {
                long long scale = it->second.first;
                long long increment = it->second.second;
                current = current * scale + increment;
                if (scale > 100) {
                    result += current;
                    current = 0;
                }
                onnumber = true;
            }
        }

        if (onnumber) {
            curstring += std::to_string(result + current);
        }

        return curstring;
    }

    bool is_valid_input(const std::string& textnum) {
        std::string input = textnum;
        std::replace(input.begin(), input.end(), '-', ' ');

        std::istringstream iss(input);
        std::string word;

        while (iss >> word) {
            if (ordinal_words.find(word) != ordinal_words.end()) {
                continue;
            }

            std::string modified = word;
            for (const auto& ending_pair : ordinal_endings) {
                const std::string& ending = ending_pair.first;
                const std::string& replacement = ending_pair.second;
                if (modified.length() >= ending.length() &&
                    modified.compare(modified.length() - ending.length(), ending.length(), ending) == 0) {
                    modified = modified.substr(0, modified.length() - ending.length()) + replacement;
                }
            }

            if (numwords.find(modified) == numwords.end()) {
                return false;
            }
        }
        return true;
    }
};