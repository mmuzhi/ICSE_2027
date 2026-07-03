#include <vector>
#include <map>
#include <array>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

class Words2Numbers {
private:
    std::map<std::string, std::array<int, 2>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::map<std::string, int> ordinalWords;
    std::vector<std::array<std::string, 2>> ordinalEndings;

public:
    Words2Numbers() {
        units = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
                 "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
                 "sixteen", "seventeen", "eighteen", "nineteen"};

        tens = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

        scales = {"hundred", "thousand", "million", "billion", "trillion"};

        numwords["and"] = {1, 0};
        for (size_t idx = 0; idx < units.size(); ++idx) {
            numwords[units[idx]] = {1, static_cast<int>(idx)};
        }
        for (size_t idx = 0; idx < tens.size(); ++idx) {
            numwords[tens[idx]] = {1, static_cast<int>(idx * 10)};
        }
        for (size_t idx = 0; idx < scales.size(); ++idx) {
            int exponent = (idx * 3 == 0) ? 2 : idx * 3;
            numwords[scales[idx]] = {static_cast<int>(std::pow(10.0, exponent)), 0};
        }

        ordinalWords["first"] = 1;
        ordinalWords["second"] = 2;
        ordinalWords["third"] = 3;
        ordinalWords["fifth"] = 5;
        ordinalWords["eighth"] = 8;
        ordinalWords["ninth"] = 9;
        ordinalWords["twelfth"] = 12;

        ordinalEndings = {
            {"ieth", "y"},
            {"th", ""}
        };
    }

    std::string text2int(const std::string& textnum) {
        std::string textnum_clean;
        for (char c : textnum) {
            if (c == '-') textnum_clean += ' ';
            else textnum_clean += c;
        }

        std::istringstream iss(textnum_clean);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        int current = 0, result = 0;
        std::string curstring;
        bool onnumber = false;

        for (const auto& w : words) {
            if (ordinalWords.find(w) != ordinalWords.end()) {
                int scale = 1;
                int increment = ordinalWords[w];
                current = current * scale + increment;
                onnumber = true;
            } else {
                std::string modified = w;
                for (const auto& ending : ordinalEndings) {
                    if (modified.size() > ending[0].size() && modified.substr(modified.size() - ending[0].size()) == ending[0]) {
                        modified = modified.substr(0, modified.size() - ending[0].size()) + ending[1];
                    }
                }

                if (numwords.find(modified) == numwords.end()) {
                    if (onnumber) {
                        curstring += std::to_string(result + current) + " ";
                    }
                    curstring += modified + " ";
                    result = current = 0;
                    onnumber = false;
                } else {
                    int scale = numwords[modified][0];
                    int increment = numwords[modified][1];
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

    bool isValidInput(const std::string& textnum) {
        std::string textnum_clean;
        for (char c : textnum) {
            if (c == '-') textnum_clean += ' ';
            else textnum_clean += c;
        }

        std::istringstream iss(textnum_clean);
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        for (const auto& w : words) {
            if (ordinalWords.find(w) != ordinalWords.end()) {
                continue;
            } else {
                std::string modified = w;
                for (const auto& ending : ordinalEndings) {
                    if (modified.size() > ending[0].size() && modified.substr(modified.size() - ending[0].size()) == ending[0]) {
                        modified = modified.substr(0, modified.size() - ending[0].size()) + ending[1];
                    }
                }

                if (numwords.find(modified) == numwords.end()) {
                    return false;
                }
            }
        }

        return true;
    }
};