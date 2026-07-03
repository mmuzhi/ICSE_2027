#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <sstream>

class NumberWordFormatter {
private:
    const std::string NUMBER[10] = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    const std::string NUMBER_TEEN[10] = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    const std::string NUMBER_TEN[9] = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
    const std::string NUMBER_MORE[4] = {"", "THOUSAND", "MILLION", "BILLION"};
    const std::string NUMBER_SUFFIX[16] = {"k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"};

    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(' ');
        size_t end = str.find_last_not_of(' ');
        if (start == std::string::npos) {
            return "";
        }
        return str.substr(start, end - start + 1);
    }

public:
    NumberWordFormatter() {}

    std::string format(const std::string& x) {
        return formatString(x);
    }

    std::string format(const char* x) {
        if (x == nullptr) {
            return "";
        }
        return formatString(std::string(x));
    }

private:
    std::string formatString(const std::string& x) {
        size_t pos = x.find('.');
        std::string lstr = (pos != std::string::npos) ? x.substr(0, pos) : x;
        std::string rstr = (pos != std::string::npos) ? x.substr(pos + 1) : "";

        std::string lstrrev = lstr;
        std::reverse(lstrrev.begin(), lstrrev.end());

        if (lstrrev.length() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.length() % 3 == 2) {
            lstrrev += "0";
        }

        int num_chunks = lstrrev.length() / 3;
        std::vector<std::string> a;
        for (int i = 0; i < num_chunks; ++i) {
            std::string chunk_rev = lstrrev.substr(3 * i, 3);
            std::string chunk = chunk_rev;
            std::reverse(chunk.begin(), chunk.end());
            a.push_back(chunk);
        }

        std::string lm_str;
        for (int i = 0; i < num_chunks; ++i) {
            if (a[i] != "000") {
                std::string part = transThree(a[i]) + " " + parseMore(i) + " ";
                lm_str = part + lm_str;
            }
        }

        std::string xs;
        if (!rstr.empty()) {
            xs = "AND CENTS " + transTwo(rstr) + " ";
        }

        std::string trimmed_lm = trim(lm_str);
        if (trimmed_lm.empty()) {
            return "ZERO ONLY";
        } else {
            return trimmed_lm + " " + xs + "ONLY";
        }
    }

    std::string transTwo(std::string s) {
        if (s.length() < 2) {
            s = std::string(2 - s.length(), '0') + s;
        }

        if (s[0] == '0') {
            std::string rest = s.substr(1);
            try {
                int num = std::stoi(rest);
                if (num < 0 || num > 9) {
                    return NUMBER[num];
                }
                return NUMBER[num];
            } catch (...) {
                return "";
            }
        } else if (s[0] == '1') {
            try {
                int num = std::stoi(s);
                return NUMBER_TEEN[num - 10];
            } catch (...) {
                return "";
            }
        } else {
            if (s.length() >= 2 && s[1] == '0') {
                int first_digit = s[0] - '0';
                return NUMBER_TEN[first_digit - 1];
            } else {
                int first_digit = s[0] - '0';
                std::string rest_str = s.substr(1);
                try {
                    int rest = std::stoi(rest_str);
                    std::string res = NUMBER_TEN[first_digit - 1];
                    if (rest > 0 && rest < 10) {
                        res += " " + NUMBER[rest];
                    } else {
                        res += " " + NUMBER[rest];
                    }
                    return res;
                } catch (...) {
                    return "";
                }
            }
        }
    }

    std::string transThree(std::string s) {
        if (s[0] == '0') {
            return transTwo(s.substr(1));
        } else {
            if (s.substr(1) == "00") {
                int first_digit = s[0] - '0';
                return NUMBER[first_digit] + " HUNDRED";
            } else {
                int first_digit = s[0] - '0';
                return NUMBER[first_digit] + " HUNDRED AND " + transTwo(s.substr(1));
            }
        }
    }

    std::string parseMore(int i) {
        if (i < 4) {
            return NUMBER_MORE[i];
        }
        return "";
    }
};