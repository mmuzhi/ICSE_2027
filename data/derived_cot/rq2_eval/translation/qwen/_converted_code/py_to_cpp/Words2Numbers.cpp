#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

class Words2Numbers {
private:
    std::map<std::string, long long> numwords_;
    std::vector<std::string> units_;
    std::vector<std::string> tens_;
    std::vector<std::string> scales_;
    std::map<std::string, int> ordinal_words_;
    std::vector<std::pair<std::string, std::string>> ordinal_endings_;

public:
    Words2Numbers() {
        units_ = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
            "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
            "sixteen", "seventeen", "eighteen", "nineteen"
        };

        tens_ = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

        scales_ = {"hundred", "thousand", "million", "billion", "trillion"};

        numwords_["and"] = 1;
        for (int i = 0; i < units_.size(); i++) {
            numwords_[units_[i]] = i;
        }
        for (int i = 0; i < tens_.size(); i++) {
            if (i == 0) continue;
            numwords_[tens_[i]] = i * 10;
        }
        for (int i = 0; i < scales_.size(); i++) {
            long long scale_val;
            if (i == 0) {
                scale_val = 100;
            } else {
                scale_val = 1;
                for (int j = 0; j < i * 3; j++) {
                    scale_val *= 10;
                }
            }
            numwords_[scales_[i]] = scale_val;
        }

        ordinal_words_ = {
            {"first", 1}, {"second", 2}, {"third", 3}, {"fifth", 5}, 
            {"eighth", 8}, {"ninth", 9}, {"twelfth", 12}
        };

        ordinal_endings_ = {
            std::make_pair("ieth", "y"),
            std::make_pair("th", "")
        };
    }

    std::string text2int(const std::string& textnum) {
        std::string numstring = textnum;
        for (char& c : numstring) {
            if (c == '-') c = ' ';
        }
        std::istringstream iss(numstring);
        std::string word;
        std::string curstring;
        long long current = 0;
        long long result = 0;
        bool onnumber = false;

        while (iss >> word) {
            if (ordinal_words_.count(word)) {
                int ordinal_value = ordinal_words_[word];
                current = current * 1 + ordinal_value;
                onnumber = true;
            } else {
                for (auto& ending : ordinal_endings_) {
                    if (word.size() >= ending.first.size() && 
                        word.substr(word.size() - ending.first.size()) == ending.first) {
                        word = word.substr(0, word.size() - ending.first.size()) + ending.second;
                        break;
                    }
                }

                if (numwords_.count(word) == 0) {
                    if (onnumber) {
                        curstring += std::to_string(result + current) + " ";
                    }
                    curstring += word + " ";
                    result = current = 0;
                    onnumber = false;
                } else {
                    long long scale = numwords_[word];
                    long long increment = 0;
                    if (numwords_.count(word) && 
                        std::is_integral<long long>::value && 
                        ordinal_words_.count(word)) {
                        increment = ordinal_words_[word];
                    } else if (numwords_.count(word)) {
                        auto it = numwords_.find(word);
                        if (it != numwords_.end()) {
                            scale = it->second;
                            if (it->second == 1) {
                                increment = 0;
                            } else {
                                increment = 0;
                            }
                        }
                    }
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
        std::string numstring = textnum;
        for (char& c : numstring) {
            if (c == '-') c = ' ';
        }
        std::istringstream iss(numstring);
        std::string word;

        while (iss >> word) {
            if (ordinal_words_.count(word)) {
                continue;
            } else {
                for (auto& ending : ordinal_endings_) {
                    if (word.size() >= ending.first.size() && 
                        word.substr(word.size() - ending.first.size()) == ending.first) {
                        word = word.substr(0, word.size() - ending.first.size()) + ending.second;
                        break;
                    }
                }

                if (numwords_.count(word) == 0) {
                    return false;
                }
            }
        }

        return true;
    }
};