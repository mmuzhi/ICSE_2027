#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

class NumberWordFormatter {
private:
    const std::string NUMBER[10] = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    const std::string NUMBER_TEEN[10] = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    const std::string NUMBER_TEN[9] = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
    const std::string NUMBER_MORE[4] = {"", "THOUSAND", "MILLION", "BILLION"};
    // NUMBER_SUFFIX is declared but never used in the original code; kept for completeness but not used.
    // const std::string NUMBER_SUFFIX[16] = {"k","w","","m","","","b","","","t","","","p","","","e"};

public:
    std::string format(const std::string& x) {
        if (x.empty()) {
            return "";
        }
        return formatString(x);
    }

    std::string formatString(const std::string& x) {
        // Split by '.'
        size_t dotPos = x.find('.');
        std::string lstr = (dotPos == std::string::npos) ? x : x.substr(0, dotPos);
        std::string rstr = (dotPos == std::string::npos) ? "" : x.substr(dotPos + 1);

        // Reverse lstr and pad to multiple of 3
        std::string lstrrev = lstr;
        std::reverse(lstrrev.begin(), lstrrev.end());
        if (lstrrev.length() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.length() % 3 == 2) {
            lstrrev += "0";
        }

        std::string lm;
        for (size_t i = 0; i < lstrrev.length() / 3; i++) {
            std::string a = lstrrev.substr(3 * i, 3);
            std::reverse(a.begin(), a.end());
            if (a != "000") {
                lm = transThree(a) + " " + parseMore(i) + " " + lm;
            } else {
                lm = transThree(a) + lm;
            }
        }

        std::string xs;
        if (!rstr.empty()) {
            xs = "AND CENTS " + transTwo(rstr) + " ";
        }

        // Trim leading/trailing spaces
        std::string trimmed = lm;
        trimmed.erase(0, trimmed.find_first_not_of(" \t\n\r"));
        trimmed.erase(trimmed.find_last_not_of(" \t\n\r") + 1);

        if (trimmed.empty()) {
            return "ZERO ONLY";
        } else {
            return trimmed + " " + xs + "ONLY";
        }
    }

private:
    std::string transTwo(const std::string& s) {
        std::string padded = s;
        if (padded.length() < 2) {
            padded = std::string(2 - padded.length(), '0') + padded;
        } else {
            padded = padded.substr(0, 2);
        }

        if (padded[0] == '0') {
            return NUMBER[std::stoi(padded.substr(1))];
        } else if (padded[0] == '1') {
            return NUMBER_TEEN[std::stoi(padded) - 10];
        } else if (padded[1] == '0') {
            return NUMBER_TEN[std::stoi(padded.substr(0, 1)) - 1];
        } else {
            return NUMBER_TEN[std::stoi(padded.substr(0, 1)) - 1] + " " + NUMBER[std::stoi(padded.substr(1))];
        }
    }

    std::string transThree(const std::string& s) {
        if (s[0] == '0') {
            return transTwo(s.substr(1));
        } else if (s.substr(1) == "00") {
            return NUMBER[std::stoi(s.substr(0, 1))] + " HUNDRED";
        } else {
            return NUMBER[std::stoi(s.substr(0, 1))] + " HUNDRED AND " + transTwo(s.substr(1));
        }
    }

    std::string parseMore(int i) {
        if (i >= 0 && i < 4) {
            return NUMBER_MORE[i];
        }
        return "";
    }
};