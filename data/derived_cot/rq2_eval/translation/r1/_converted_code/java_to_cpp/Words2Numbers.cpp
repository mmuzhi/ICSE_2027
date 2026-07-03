#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <cctype>

class Words2Numbers {
private:
    std::unordered_map<std::string, std::pair<int, int>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::unordered_map<std::string, int> ordinalWords;
    std::vector<std::vector<std::string>> ordinalEndings;

    std::string convertOrdinalWord(std::string word) const {
        for (const auto& ending : ordinalEndings) {
            if (word.size() >= ending[0].size() && 
                word.substr(word.size() - ending[0].size()) == ending[0]) {
                word = word.substr(0, word.size() - ending[0].size()) + ending[1];
            }
        }
        return word;
    }

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

        numwords["and"] = std::make_pair(1, 0);
        for (int idx = 0; idx < units.size(); idx++) {
            numwords[units[idx]] = std::make_pair(1, idx);
        }
        for (int idx = 0; idx < tens.size(); idx++) {
            if (!tens[idx].empty()) {
                numwords[tens[idx]] = std::make_pair(1, idx * 10);
            }
        }
        for (int idx = 0; idx < scales.size(); idx++) {
            int exponent = (idx == 0) ? 2 : idx * 3;
            int value = static_cast<int>(std::pow(10, exponent));
            numwords[scales[idx]] = std::make_pair(value, 0);
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

    std::string text2int(const std::string& textnum) {
        std::string processed = textnum;
        std::replace(processed.begin(), processed.end(), '-', ' ');
        
        std::istringstream iss(processed);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        int current = 0;
        int result = 0;
        std::ostringstream oss;
        bool onnumber = false;

        for (const auto& originalWord : words) {
            if (ordinalWords.find(originalWord) != ordinalWords.end()) {
                int increment = ordinalWords.at(originalWord);
                current = current * 1 + increment;
                onnumber = true;
            } else {
                std::string word = convertOrdinalWord(originalWord);
                if (numwords.find(word) == numwords.end()) {
                    if (onnumber) {
                        oss << (result + current) << " ";
                        result = 0;
                        current = 0;
                    }
                    oss << originalWord << " ";
                    onnumber = false;
                } else {
                    auto p = numwords.at(word);
                    int scale = p.first;
                    int increment = p.second;
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
            oss << (result + current);
        }

        return oss.str();
    }

    bool is_valid_input(const std::string& textnum) {
        std::string processed = textnum;
        std::replace(processed.begin(), processed.end(), '-', ' ');
        
        std::istringstream iss(processed);
        std::string word;
        while (iss >> word) {
            if (ordinalWords.find(word) != ordinalWords.end()) {
                continue;
            } else {
                std::string converted = convertOrdinalWord(word);
                if (numwords.find(converted) == numwords.end()) {
                    return false;
                }
            }
        }
        return true;
    }
};