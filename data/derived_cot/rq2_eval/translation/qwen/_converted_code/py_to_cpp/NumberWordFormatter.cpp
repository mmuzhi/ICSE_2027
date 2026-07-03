#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>

class NumberWordFormatter {
private:
    const std::array<std::string, 10> NUMBER = {{"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"}};
    const std::array<std::string, 10> NUMBER_TEEN = {{"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"}};
    const std::array<std::string, 9> NUMBER_TEN = {{"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"}};
    const std::array<std::string, 4> NUMBER_MORE = {{"", "THOUSAND", "MILLION", "BILLION"}};

public:
    std::string format(double x) {
        if (std::isnan(x)) {
            return "";
        }
        return format_string(std::to_string(x));
    }

    std::string format_string(const std::string& x) {
        size_t pos = x.find('.');
        std::string lstr, rstr;
        if (pos == std::string::npos) {
            lstr = x;
            rstr = "";
        } else {
            lstr = x.substr(0, pos);
            rstr = x.substr(pos + 1);
        }

        if (lstr.empty() && rstr.empty()) {
            return "ZERO ONLY";
        }

        std::string reversed = std::string(lstr.rbegin(), lstr.rend());
        if (reversed.length() % 3 == 1) {
            reversed += "00";
        } else if (reversed.length() % 3 == 2) {
            reversed += "0";
        }

        int chunks = reversed.length() / 3;
        std::string result;
        for (int i = 0; i < chunks; ++i) {
            std::string chunk = reversed.substr(i * 3, 3);
            if (chunk != "000") {
                std::string word = trans_three(chunk);
                if (!word.empty()) {
                    if (!result.empty()) {
                        word += " " + NUMBER_MORE[i];
                    }
                    result = word + " " + result;
                }
            }
        }

        std::string decimalPart;
        if (!rstr.empty()) {
            decimalPart = "AND CENTS " + trans_two(rstr) + " ";
        } else if (result.empty()) {
            return "ZERO ONLY";
        }

        if (result.empty()) {
            return "ZERO ONLY";
        }

        return result + decimalPart + "ONLY";
    }

    std::string trans_two(const std::string& s) {
        std::string padded = s;
        if (padded.length() < 2) {
            padded = "0" + padded;
        }
        if (padded[0] == '0') {
            return NUMBER[std::stoi(padded.substr(1, 1))];
        } else if (padded[0] == '1') {
            return NUMBER_TEEN[std::stoi(padded) - 10];
        } else if (padded[1] == '0') {
            return NUMBER_TEN[std::stoi(padded.substr(0, 1)) - 1];
        } else {
            return NUMBER_TEN[std::stoi(padded.substr(0, 1)) - 1] + " " + NUMBER[std::stoi(padded.substr(1, 1))];
        }
    }

    std::string trans_three(const std::string& s) {
        if (s[0] == '0') {
            return trans_two(s.substr(1));
        } else {
            std::string hundreds = NUMBER[std::stoi(std::string(1, s[0]))];
            if (s.substr(1) == "00") {
                return hundreds + " HUNDRED";
            } else {
                return hundreds + " HUNDRED AND " + trans_two(s.substr(1));
            }
        }
    }
};