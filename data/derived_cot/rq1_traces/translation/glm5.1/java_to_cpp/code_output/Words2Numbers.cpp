#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <utility>

class Words2Numbers {
private:
    std::unordered_map<std::string, std::pair<int, int>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::unordered_map<std::string, int> ordinalWords;
    std::vector<std::pair<std::string, std::string>> ordinalEndings;

    static std::vector<std::string> split_space(const std::string& s) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = s.find(' ');
        bool found_delimiter = false;
        while (end != std::string::npos) {
            found_delimiter = true;
            tokens.push_back(s.substr(start, end - start));
            start = end + 1;
            end = s.find(' ', start);
        }
        tokens.push_back(s.substr(start));

        if (found_delimiter) {
            while (!tokens.empty() && tokens.back().empty()) {
                tokens.pop_back();
            }
        }

        return tokens;
    }

    static std::string replace_char(const std::string& s, char from, char to) {
        std::string result = s;
        for (char& c : result) {
            if (c == from) c = to;
        }
        return result;
    }

    static bool ends_with(const std::string& s, const std::string& suffix) {
        if (suffix.size() > s.size()) return false;
        return s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    static int int_pow(int base, int exp) {
        int result = 1;
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
        return result;
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

        numwords["and"] = {1, 0};
        for (int idx = 0; idx < static_cast<int>(units.size()); idx++) {
            numwords[units[idx]] = {1, idx};
        }
        for (int idx = 0; idx < static_cast<int>(tens.size()); idx++) {
            numwords[tens[idx]] = {1, idx * 10};
        }
        for (int idx = 0; idx < static_cast<int>(scales.size()); idx++) {
            int exponent = (idx * 3 == 0 ? 2 : idx * 3);
            numwords[scales[idx]] = {int_pow(10, exponent), 0};
        }

        ordinalWords["first"] = 1;
        ordinalWords["second"] = 2;
        ordinalWords["third"] = 3;
        ordinalWords["fifth"] = 5;
        ordinalWords["eighth"] = 8;
        ordinalWords["ninth"] = 9;
        ordinalWords["twelfth"] = 12;

        ordinalEndings = {
            {"ieth", "y"}, {"th", ""}
        };
    }

    std::string text2int(const std::string& textnum_input) {
        std::string textnum = replace_char(textnum_input, '-', ' ');

        int current = 0, result = 0;
        std::stringstream curstring;
        bool onnumber = false;

        std::vector<std::string> words = split_space(textnum);
        for (std::string word : words) {
            if (ordinalWords.find(word) != ordinalWords.end()) {
                int scale = 1, increment = ordinalWords[word];
                current = current * scale + increment;
                onnumber = true;
            } else {
                for (const auto& ending : ordinalEndings) {
                    if (ends_with(word, ending.first)) {
                        word = word.substr(0, word.length() - ending.first.length()) + ending.second;
                    }
                }

                if (numwords.find(word) == numwords.end()) {
                    if (onnumber) {
                        curstring << (result + current) << " ";
                    }
                    curstring << word << " ";
                    result = current = 0;
                    onnumber = false;
                } else {
                    int scale = numwords[word].first;
                    int increment = numwords[word].second;
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
            curstring << (result + current);
        }

        return curstring.str();
    }

    bool isValidInput(const std::string& textnum_input) {
        std::string textnum = replace_char(textnum_input, '-', ' ');

        std::vector<std::string> words = split_space(textnum);
        for (std::string word : words) {
            if (ordinalWords.find(word) != ordinalWords.end()) {
                continue;
            } else {
                for (const auto& ending : ordinalEndings) {
                    if (ends_with(word, ending.first)) {
                        word = word.substr(0, word.length() - ending.first.length()) + ending.second;
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