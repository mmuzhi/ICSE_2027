#include <string>
#include <vector>
#include <sstream>
#include <optional>
#include <algorithm>

class NumberWordFormatter {
private:
    std::vector<std::string> NUMBER = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    std::vector<std::string> NUMBER_TEEN = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    std::vector<std::string> NUMBER_TEN = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
    std::vector<std::string> NUMBER_MORE = {"", "THOUSAND", "MILLION", "BILLION"};
    std::vector<std::string> NUMBER_SUFFIX = {"k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"};

    static std::string trim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        size_t end = s.find_last_not_of(" \t\n\r");
        return s.substr(start, end - start + 1);
    }

public:
    NumberWordFormatter() = default;

    std::string format(const std::optional<double>& x) {
        if (x.has_value()) {
            std::ostringstream oss;
            oss << x.value();
            return format_string(oss.str());
        }
        return "";
    }

    std::string format_string(const std::string& x) {
        // Split on '.', matching Python's (x.split('.') + [''])[:2]
        std::vector<std::string> parts;
        std::string part;
        for (char c : x) {
            if (c == '.') {
                parts.push_back(part);
                part.clear();
            } else {
                part += c;
            }
        }
        parts.push_back(part);

        std::string lstr = parts[0];
        std::string rstr = (parts.size() > 1) ? parts[1] : "";

        std::string lstrrev = lstr;
        std::reverse(lstrrev.begin(), lstrrev.end());

        if (lstrrev.size() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.size() % 3 == 2) {
            lstrrev += "0";
        }

        std::string lm;
        for (size_t i = 0; i < lstrrev.size() / 3; i++) {
            std::string ai = lstrrev.substr(3 * i, 3);
            std::reverse(ai.begin(), ai.end());
            if (ai != "000") {
                lm = trans_three(ai) + " " + parse_more(static_cast<int>(i)) + " " + lm;
            } else {
                lm += trans_three(ai);
            }
        }

        std::string xs = rstr.empty() ? "" : "AND CENTS " + trans_two(rstr) + " ";
        std::string lm_trimmed = trim(lm);

        if (lm_trimmed.empty()) {
            return "ZERO ONLY";
        } else {
            return lm_trimmed + " " + xs + "ONLY";
        }
    }

    std::string trans_two(std::string s) {
        if (s.size() < 2) s = std::string(2 - s.size(), '0') + s;

        if (s[0] == '0') {
            return NUMBER[s[1] - '0'];
        } else if (s[0] == '1') {
            return NUMBER_TEEN[std::stoi(s) - 10];
        } else if (s[1] == '0') {
            return NUMBER_TEN[s[0] - '0' - 1];
        } else {
            return NUMBER_TEN[s[0] - '0' - 1] + " " + NUMBER[s[1] - '0'];
        }
    }

    std::string trans_three(std::string s) {
        if (s[0] == '0') {
            return trans_two(s.substr(1));
        } else if (s.substr(1) == "00") {
            return NUMBER[s[0] - '0'] + " HUNDRED";
        } else {
            return NUMBER[s[0] - '0'] + " HUNDRED AND " + trans_two(s.substr(1));
        }
    }

    std::string parse_more(int i) {
        if (i >= 0 && i < static_cast<int>(NUMBER_MORE.size())) {
            return NUMBER_MORE[i];
        }
        return "";
    }
};