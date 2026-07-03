#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <cstdint>

class Words2Numbers {
private:
    std::unordered_map<std::string, std::pair<int, int>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::unordered_map<std::string, int> ordinalWords;
    std::vector<std::pair<std::string, std::string>> ordinalEndings;

public:
    Words2Numbers() {
        units = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
            "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
            "sixteen", "seventeen", "eighteen", "nineteen"
        };
        tens = {
            "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
        };
        scales = {
            "hundred", "thousand", "million", "billion", "trillion"
        };

        numwords["and"] = {1, 0};
        for (size_t idx = 0; idx < units.size(); ++idx) {
            numwords[units[idx]] = {1, static_cast<int>(idx)};
        }
        for (size_t idx = 0; idx < tens.size(); ++idx) {
            if (!tens[idx].empty()) {
                numwords[tens[idx]] = {1, static_cast<int>(idx * 10)};
            }
        }
        for (size_t idx = 0; idx < scales.size(); ++idx) {
            int scale = static_cast<int>(std::pow(10, (idx * 3 == 0) ? 2 : static_cast<int>(idx * 3)));
            numwords[scales[idx]] = {scale, 0};
        }

        ordinalWords["first"] = 1;
        ordinalWords["second"] = 2;
        ordinalWords["third"] = 3;
        ordinalWords["fifth"] = 5;
        ordinalWords["eighth"] = 8;
        ordinalWords["ninth"] = 9;
        ordinalWords["twelfth"] = 12;

        ordinalEndings = {{"ieth", "y"}, {"th", ""}};
    }

    std::string text2int(std::string textnum) {
        // replace hyphens with spaces
        for (auto &ch : textnum) {
            if (ch == '-') ch = ' ';
        }

        int current = 0, result = 0;
        std::ostringstream curstring;
        bool onnumber = false;

        std::istringstream iss(textnum);
        std::string word;
        while (iss >> word) {
            // check ordinalWords first
            auto it = ordinalWords.find(word);
            if (it != ordinalWords.end()) {
                int scale = 1;
                int increment = it->second;
                current = current * scale + increment;
                onnumber = true;
                continue;
            }

            // try ordinal endings
            for (const auto &ending : ordinalEndings) {
                const std::string &suffix = ending.first;
                const std::string &replacement = ending.second;
                if (word.size() >= suffix.size() &&
                    word.substr(word.size() - suffix.size()) == suffix) {
                    word = word.substr(0, word.size() - suffix.size()) + replacement;
                }
            }

            auto it2 = numwords.find(word);
            if (it2 == numwords.end()) {
                // not a number word
                if (onnumber) {
                    curstring << (result + current) << " ";
                }
                curstring << word << " ";
                result = current = 0;
                onnumber = false;
            } else {
                int scale = it2->second.first;
                int increment = it2->second.second;
                current = current * scale + increment;
                if (scale > 100) {
                    result += current;
                    current = 0;
                }
                onnumber = true;
            }
        }

        if (onnumber) {
            curstring << (result + current);
        }

        return curstring.str();
    }

    bool isValidInput(std::string textnum) {
        // replace hyphens with spaces
        for (auto &ch : textnum) {
            if (ch == '-') ch = ' ';
        }

        std::istringstream iss(textnum);
        std::string word;
        while (iss >> word) {
            if (ordinalWords.count(word)) {
                continue;
            }

            for (const auto &ending : ordinalEndings) {
                const std::string &suffix = ending.first;
                const std::string &replacement = ending.second;
                if (word.size() >= suffix.size() &&
                    word.substr(word.size() - suffix.size()) == suffix) {
                    word = word.substr(0, word.size() - suffix.size()) + replacement;
                }
            }

            if (!numwords.count(word)) {
                return false;
            }
        }

        return true;
    }
};