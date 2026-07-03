#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cmath>
#include <array>

class Words2Numbers {
private:
    std::unordered_map<std::string, std::array<int, 2>> numwords;
    std::vector<std::string> units;
    std::vector<std::string> tens;
    std::vector<std::string> scales;
    std::unordered_map<std::string, int> ordinalWords;
    std::vector<std::array<std::string, 2>> ordinalEndings;

    static bool endsWith(const std::string& str, const std::string& suffix) {
        if (suffix.size() > str.size()) return false;
        return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
    }

    static std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream iss(s);
        while (std::getline(iss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
        size_t pos = 0;
        while ((pos = str.find(from, pos)) != std::string::npos) {
            str.replace(pos, from.length(), to);
            pos += to.length();
        }
        return str;
    }

public:
    Words2Numbers() {
        units = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
                 "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
                 "sixteen", "seventeen", "eighteen", "nineteen"};
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
            int exp = (idx * 3 == 0) ? 2 : idx * 3;
            numwords[scales[idx]] = {(int)std::pow(10, exp), 0};
        }

        ordinalWords["first"] = 1;
        ordinalWords["second"] = 2;
        ordinalWords["third"] = 3;
        ordinalWords["fifth"] = 5;
        ordinalWords["eighth"] = 8;
        ordinalWords["ninth"] = 9;
        ordinalWords["twelfth"] = 12;

        ordinalEndings = {{{"ieth", "y"}}, {{"th", ""}}};
    }

    std::string text2int(std::string textnum) {
        textnum = replaceAll(textnum, "-", " ");

        int current = 0, result = 0;
        std::string curstring;
        bool onnumber = false;

        for (const std::string& word : split(textnum, ' ')) {
            std::string w = word;
            if (ordinalWords.count(word)) {
                int scale = 1, increment = ordinalWords[word];
                current = current * scale + increment;
                onnumber = true;
            } else {
                for (const auto& ending : ordinalEndings) {
                    if (endsWith(w, ending[0])) {
                        w = w.substr(0, w.length() - ending[0].length()) + ending[1];
                    }
                }

                if (!numwords.count(w)) {
                    if (onnumber) {
                        curstring += std::to_string(result + current) + " ";
                    }
                    curstring += w + " ";
                    result = current = 0;
                    onnumber = false;
                } else {
                    int scale = numwords[w][0];
                    int increment = numwords[w][1];
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

    bool isValidInput(std::string textnum) {
        textnum = replaceAll(textnum, "-", " ");

        for (const std::string& word : split(textnum, ' ')) {
            std::string w = word;
            if (ordinalWords.count(w)) {
                continue;
            } else {
                for (const auto& ending : ordinalEndings) {
                    if (endsWith(w, ending[0])) {
                        w = w.substr(0, w.length() - ending[0].length()) + ending[1];
                    }
                }

                if (!numwords.count(w)) {
                    return false;
                }
            }
        }

        return true;
    }
};