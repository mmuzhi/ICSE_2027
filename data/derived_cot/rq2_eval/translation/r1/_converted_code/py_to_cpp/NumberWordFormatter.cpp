#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

class NumberWordFormatter {
private:
    std::vector<std::string> NUMBER;
    std::vector<std::string> NUMBER_TEEN;
    std::vector<std::string> NUMBER_TEN;
    std::vector<std::string> NUMBER_MORE;

public:
    NumberWordFormatter() {
        NUMBER = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
        NUMBER_TEEN = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
        NUMBER_TEN = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
        NUMBER_MORE = {"", "THOUSAND", "MILLION", "BILLION"};
    }

    std::string format(int x) {
        return format_string(std::to_string(x));
    }

    std::string format(double x) {
        std::ostringstream oss;
        oss << std::fixed << x;
        std::string s = oss.str();

        size_t pos = s.find('.');
        if (pos != std::string::npos) {
            size_t last_non_zero = s.find_last_not_of('0');
            if (last_non_zero == pos) {
                s = s.substr(0, pos+1) + "0";
            } else if (last_non_zero != std::string::npos) {
                s = s.substr(0, last_non_zero+1);
            } else {
                s = s.substr(0, pos);
            }
        }
        return format_string(s);
    }

    std::string format_string(const std::string& x) {
        size_t pos = x.find('.');
        std::string lstr, rstr;
        if (pos != std::string::npos) {
            lstr = x.substr(0, pos);
            rstr = x.substr(pos+1);
        } else {
            lstr = x;
            rstr = "";
        }

        if (lstr.empty()) {
            lstr = "0";
        }

        std::string lstrrev(lstr.rbegin(), lstr.rend());
        if (lstrrev.length() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.length() % 3 == 2) {
            lstrrev += "0";
        }

        int chunks = lstrrev.length() / 3;
        std::vector<std::string> a(chunks, "");
        std::string lm = "";

        for (int i = 0; i < chunks; i++) {
            std::string chunk = lstrrev.substr(3*i, 3);
            std::reverse(chunk.begin(), chunk.end());
            a[i] = chunk;

            if (a[i] != "000") {
                std::string current = trans_three(a[i]);
                std::string more = parse_more(i);
                if (!more.empty()) {
                    current = current + " " + more;
                }
                if (!current.empty()) {
                    if (lm.empty()) {
                        lm = current;
                    } else {
                        lm = current + " " + lm;
                    }
                }
            }
        }

        std::string xs = "";
        if (!rstr.empty()) {
            xs = "AND CENTS " + trans_two(rstr) + " ";
        }

        if (lm.empty()) {
            return "ZERO ONLY";
        } else {
            return lm + " " + xs + "ONLY";
        }
    }

private:
    std::string trans_two(std::string s) {
        if (s.length() < 2) {
            s = std::string(2 - s.length(), '0') + s;
        }

        if (s[0] == '0') {
            int idx = s[1] - '0';
            if (idx >= 0 && idx < 10) {
                return NUMBER[idx];
            } else {
                return "";
            }
        } else if (s[0] == '1') {
            int value = std::stoi(s);
            if (value >= 10 && value <= 19) {
                return NUMBER_TEEN[value - 10];
            } else {
                return "";
            }
        } else {
            int ten_idx = s[0] - '0' - 1;
            if (ten_idx < 0 || ten_idx >= NUMBER_TEN.size()) {
                return "";
            }
            std::string ten_part = NUMBER_TEN[ten_idx];
            if (s[1] == '0') {
                return ten_part;
            } else {
                int digit = s[1] - '0';
                if (digit < 0 || digit >= NUMBER.size()) {
                    return ten_part;
                }
                std::string digit_part = NUMBER[digit];
                return ten_part + " " + digit_part;
            }
        }
    }

    std::string trans_three(std::string s) {
        if (s.length() < 3) {
            s = std::string(3 - s.length(), '0') + s;
        }

        if (s[0] == '0') {
            return trans_two(s.substr(1));
        } else {
            int hundreds_digit = s[0] - '0';
            if (hundreds_digit < 0 || hundreds_digit >= NUMBER.size()) {
                return "";
            }
            std::string hundreds_part = NUMBER[hundreds_digit] + " HUNDRED";
            std::string rest = s.substr(1);
            if (rest == "00") {
                return hundreds_part;
            } else {
                std::string two_digits = trans_two(rest);
                if (two_digits.empty()) {
                    return hundreds_part;
                } else {
                    return hundreds_part + " AND " + two_digits;
                }
            }
        }
    }

    std::string parse_more(int i) {
        if (i >= 0 && i < NUMBER_MORE.size()) {
            return NUMBER_MORE[i];
        }
        return "";
    }
};