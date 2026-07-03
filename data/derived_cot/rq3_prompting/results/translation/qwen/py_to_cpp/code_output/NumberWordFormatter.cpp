#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class NumberWordFormatter {
private:
    std::vector<std::string> NUMBER = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    std::vector<std::string> NUMBER_TEEN = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    std::vector<std::string> NUMBER_TEN = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
    std::vector<std::string> NUMBER_MORE = {"", "THOUSAND", "MILLION", "BILLION"};

public:
    NumberWordFormatter() {}

    std::string format(long x) {
        if (x == 0) {
            return "ZERO ONLY";
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

        if (lstr.empty()) {
            lstr = "0";
        }

        std::reverse(lstr.begin(), lstr.end());
        while (lstr.length() % 3 != 0) {
            lstr += '0';
        }

        std::string lm = "";
        for (size_t i = 0; i < lstr.length(); i += 3) {
            std::string chunk = lstr.substr(i, 3);
            std::reverse(chunk.begin(), chunk.end());
            if (chunk != "000") {
                std::string chunk_words = trans_three(chunk);
                std::string suffix = parse_more(i / 3);
                lm = chunk_words + " " + suffix + " " + lm;
            }
        }

        std::string decimal_words = "";
        if (!rstr.empty()) {
            if (rstr.length() > 2) {
                rstr = rstr.substr(0, 2);
            }
            decimal_words = "AND CENTS " + trans_two(rstr) + " ";
        }

        if (lm.empty()) {
            return "ZERO " + decimal_words + "ONLY";
        } else {
            std::string result = lm + decimal_words + "ONLY";
            // Remove trailing spaces
            if (!result.empty()) {
                size_t last_pos = result.find_last_not_of(' ');
                if (last_pos != std::string::npos) {
                    result = result.substr(0, last_pos + 1);
                }
            }
            return result;
        }
    }

    std::string trans_two(const std::string& s) {
        std::string s2 = s;
        while (s2.length() < 2) {
            s2 = "0" + s2;
        }
        if (s2[0] == '0') {
            return NUMBER[s2[1] - '0'];
        } else if (s2[0] == '1') {
            return NUMBER_TEEN[s2[0] - '1' + 0];
        } else if (s2[1] == '0') {
            return NUMBER_TEN[s2[0] - '0' - 1];
        } else {
            return NUMBER_TEN[s2[0] - '0' - 1] + " " + NUMBER[s2[1] - '0'];
        }
    }

    std::string trans_three(const std::string& s) {
        if (s[0] == '0') {
            return trans_two(s.substr(1));
        } else if (s.substr(1) == "00") {
            return NUMBER[s[0] - '0'] + " HUNDRED";
        } else {
            return NUMBER[s[0] - '0'] + " HUNDRED AND " + trans_two(s.substr(1));
        }
    }

    std::string parse_more(int i) {
        if (i < NUMBER_MORE.size()) {
            return NUMBER_MORE[i];
        } else {
            return "";
        }
    }
};