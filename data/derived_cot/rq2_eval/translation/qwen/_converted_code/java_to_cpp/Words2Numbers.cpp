#include <iostream>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <cmath>
#include <sstream>
#include <string>

class Words2Numbers {

private:
    std::unordered_map<std::string, std::vector<int>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::unordered_map<std::string, int> ordinalWords;
    std::vector<std::vector<std::string>> ordinalEndings;

public:
    Words2Numbers() {
        units = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", 
                 "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
                 "sixteen", "seventeen", "eighteen", "nineteen"};
        tens = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
        scales = {"hundred", "thousand", "million", "billion", "trillion"};

        numwords["and"] = {1, 0};
        for (int idx = 0; idx < units.size(); idx++) {
            numwords[units[idx]] = {1, idx};
        }
        for (int idx = 0; idx < tens.size(); idx++) {
            numwords[tens[idx]] = {1, idx * 10};
        }
        for (int idx = 0; idx < scales.size(); idx++) {
            int exponent = (idx == 0) ? 2 : idx * 3;
            numwords[scales[idx]] = {static_cast<int>(std::pow(10, exponent)), 0};
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
        size_t pos = 0;
        while (pos < processed.size()) {
            if (processed[pos] == '-') {
                processed.replace(pos, 1, " ");
                pos += 2; // Skip the space added
            } else {
                pos++;
            }
        }

        int current = 0, result = 0;
        std::string currentStr;
        bool onnumber = false;

        std::istringstream iss(processed);
        std::string word;
        while (iss >> word) {
            if (ordinalWords.find(word) != ordinalWords.end()) {
                int scale = 1;
                int increment = ordinalWords[word];
                current = current * scale + increment;
                onnumber = true;
            } else {
                for (const auto& ending : ordinalEndings) {
                    if (word.size() >= ending[0].size() && 
                        word.substr(word.size() - ending[0].size()) == ending[0]) {
                        word = word.substr(0, word.size() - ending[0].size()) + ending[1];
                    }
                }

                if (numwords.find(word) == numwords.end()) {
                    if (onnumber) {
                        currentStr += std::to_string(result + current) + " ";
                    }
                    currentStr += word + " ";
                    result = current = 0;
                    onnumber = false;
                } else {
                    int scale = numwords[word][0];
                    int increment = numwords[word][1];
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
            currentStr += std::to_string(result + current);
        }

        return currentStr;
    }

    bool is_valid_input(const std::string& textnum) {
        std::string processed = textnum;
        size_t pos = 0;
        while (pos < processed.size()) {
            if (processed[pos] == '-') {
                processed.replace(pos, 1, " ");
                pos += 2;
            } else {
                pos++;
            }
        }

        std::istringstream iss(processed);
        std::string word;

        while (iss >> word) {
            if (ordinalWords.find(word) != ordinalWords.end()) {
                continue;
            } else {
                for (const auto& ending : ordinalEndings) {
                    if (word.size() >= ending[0].size() && 
                        word.substr(word.size() - ending[0].size()) == ending[0]) {
                        word = word.substr(0, word.size() - ending[0].size()) + ending[1];
                    }
                }

                if (numwords.find(word) == numwords.end()) {
                    return false;
                }
            }
        }

        return true;
    }
};