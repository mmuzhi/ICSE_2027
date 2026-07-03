#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

class NumberWordFormatter {
private:
    std::vector<std::string> NUMBER;
    std::vector<std::string> NUMBER_TEEN;
    std::vector<std::string> NUMBER_TEN;
    std::vector<std::string> NUMBER_MORE;
    std::vector<std::string> NUMBER_SUFFIX; // kept for completeness, unused

    // Trim leading/trailing spaces
    static std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(' ');
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(' ');
        return s.substr(start, end - start + 1);
    }

    // Convert double to string matching Python's str() behavior:
    // uses default formatting, but appends ".0" for whole numbers.
    static std::string double_to_string(double d) {
        std::ostringstream oss;
        oss << d;
        std::string s = oss.str();
        // If no decimal point and no exponent, add ".0"
        if (s.find('.') == std::string::npos &&
            s.find('e') == std::string::npos &&
            s.find('E') == std::string::npos) {
            s += ".0";
        }
        return s;
    }

public:
    NumberWordFormatter() {
        NUMBER = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
        NUMBER_TEEN = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN",
                       "EIGHTEEN", "NINETEEN"};
        NUMBER_TEN = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
        NUMBER_MORE = {"", "THOUSAND", "MILLION", "BILLION"};
        NUMBER_SUFFIX = {"k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"};
    }

    std::string format(int x) {
        return format_string(std::to_string(x));
    }

    std::string format(double x) {
        return format_string(double_to_string(x));
    }

    std::string format_string(const std::string& x) {
        // Split into integer and decimal parts
        std::string lstr, rstr;
        size_t dot = x.find('.');
        if (dot == std::string::npos) {
            lstr = x;
            rstr = "";
        } else {
            lstr = x.substr(0, dot);
            rstr = x.substr(dot + 1);
        }

        // Reverse integer part and pad to multiple of 3
        std::string lstrrev(lstr.rbegin(), lstr.rend());
        if (lstrrev.length() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.length() % 3 == 2) {
            lstrrev += "0";
        }

        // Process groups of three digits from least significant
        std::string a[5];
        std::string lm;
        int groups = lstrrev.length() / 3;
        for (int i = 0; i < groups; ++i) {
            std::string block = lstrrev.substr(3 * i, 3);
            std::string block_rev(block.rbegin(), block.rend()); // reverse back
            a[i] = block_rev;
            if (a[i] != "000") {
                lm = trans_three(a[i]) + " " + parse_more(i) + " " + lm;
            } else {
                lm += trans_three(a[i]); // adds empty string
            }
        }

        // Build decimal part string
        std::string xs;
        if (!rstr.empty()) {
            xs = "AND CENTS " + trans_two(rstr) + " ";
        }

        // Final assembly
        std::string trimmed_lm = trim(lm);
        if (trimmed_lm.empty()) {
            return "ZERO ONLY";
        } else {
            return trimmed_lm + " " + xs + "ONLY";
        }
    }

    std::string trans_two(const std::string& s) {
        // Pad to length 2
        std::string padded = s;
        if (padded.length() < 2) {
            padded = std::string(2 - padded.length(), '0') + padded;
        }

        if (padded[0] == '0') {
            return NUMBER[padded[1] - '0'];
        } else if (padded[0] == '1') {
            int idx = (padded[0] - '0') * 10 + (padded[1] - '0') - 10;
            return NUMBER_TEEN[idx];
        } else if (padded[1] == '0') {
            return NUMBER_TEN[padded[0] - '1'];
        } else {
            return NUMBER_TEN[padded[0] - '1'] + " " + NUMBER[padded[1] - '0'];
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
        return NUMBER_MORE[i];
    }
};