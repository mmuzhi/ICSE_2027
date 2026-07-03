#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class NumberWordFormatter {
private:
    const std::vector<std::string> NUMBER = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    const std::vector<std::string> NUMBER_TEEN = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    const std::vector<std::string> NUMBER_TEN = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
    const std::vector<std::string> NUMBER_MORE = {"", "THOUSAND", "MILLION", "BILLION"};
    const std::vector<std::string> NUMBER_SUFFIX = {"k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"};

    static std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\n\r");
        return s.substr(start, end - start + 1);
    }

    static std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> parts;
        std::istringstream iss(s);
        std::string part;
        while (std::getline(iss, part, delim)) {
            parts.push_back(part);
        }
        return parts;
    }

    static std::string reverseStr(const std::string& s) {
        std::string r = s;
        std::reverse(r.begin(), r.end());
        return r;
    }

public:
    std::string format(std::nullptr_t) {
        return "";
    }

    std::string format(const std::string& x) {
        return formatString(x);
    }

    std::string formatString(std::string x) {
        std::vector<std::string> parts = split(x, '.');
        std::string lstr = parts[0];
        std::string rstr = parts.size() > 1 ? parts[1] : "";
        std::string lstrrev = reverseStr(lstr);
        std::vector<std::string> a(5);

        if (lstrrev.length() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.length() % 3 == 2) {
            lstrrev += "0";
        }

        std::string lm;
        for (size_t i = 0; i < lstrrev.length() / 3; i++) {
            a[i] = reverseStr(lstrrev.substr(3 * i, 3));
            if (a[i] != "000") {
                lm = transThree(a[i]) + " " + parseMore(static_cast<int>(i)) + " " + lm;
            } else {
                lm = transThree(a[i]) + lm;
            }
        }

        std::string xs = !rstr.empty() ? "AND CENTS " + transTwo(rstr) + " " : "";
        if (trim(lm).empty()) {
            return "ZERO ONLY";
        } else {
            return trim(lm) + " " + xs + "ONLY";
        }
    }

    std::string transTwo(std::string s) {
        if (s.length() < 2) {
            s = std::string(2 - s.length(), '0') + s;
        }
        if (s[0] == '0') {
            return NUMBER[std::stoi(s.substr(1))];
        } else if (s[0] == '1') {
            return NUMBER_TEEN[std::stoi(s) - 10];
        } else if (s[1] == '0') {
            return NUMBER_TEN[std::stoi(s.substr(0, 1)) - 1];
        } else {
            return NUMBER_TEN[std::stoi(s.substr(0, 1)) - 1] + " " + NUMBER[std::stoi(s.substr(1))];
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
        return NUMBER_MORE[i];
    }
};