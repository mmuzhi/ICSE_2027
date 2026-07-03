#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

class NumberWordFormatter {
private:
    const std::vector<std::string> NUMBER = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    const std::vector<std::string> NUMBER_TEEN = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    const std::vector<std::string> NUMBER_TEN = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
    const std::vector<std::string> NUMBER_MORE = {"", "THOUSAND", "MILLION", "BILLION"};

public:
    std::string format(const std::string& x) {
        if (x.empty()) {
            return "";
        }
        return formatString(x);
    }

    std::string formatString(const std::string& x) {
        size_t pos = x.find('.');
        std::string lstr = x.substr(0, pos);
        std::string rstr = (pos == std::string::npos) ? "" : x.substr(pos + 1);

        if (lstr.empty()) {
            lstr = "0";
        }

        std::string lstrrev = lstr;
        std::reverse(lstrrev.begin(), lstrrev.end());

        if (lstrrev.length() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.length() % 3 == 2) {
            lstrrev += "0";
        }

        std::vector<std::string> chunks;
        for (size_t i = 0; i < lstrrev.length(); i += 3) {
            std::string chunk = lstrrev.substr(i, 3);
            std::reverse(chunk.begin(), chunk.end());
            chunks.push_back(chunk);
        }

        std::string lm;
        for (int i = chunks.size() - 1; i >= 0; i--) {
            if (chunks[i] == "000") {
                continue;
            }
            std::string word = transThree(chunks[i]);
            if (!word.empty()) {
                std::string scale = parseMore(i);
                if (!scale.empty()) {
                    lm = word + " " + scale + " " + lm;
                } else {
                    lm = word + " " + lm;
                }
            }
        }

        std::string xs;
        if (!rstr.empty()) {
            xs = "AND CENTS " + transTwo(rstr) + " ";
        }

        if (lm.empty()) {
            return "ZERO ONLY";
        } else {
            return lm + xs + "ONLY";
        }
    }

    std::string transTwo(const std::string& s) {
        s = StringFormatter::padLeft(s, '0', 2);
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
        } else if (s[1] == '0' && s[2] == '0') {
            return NUMBER[std::stoi(s.substr(0, 1))] + " HUNDRED";
        } else {
            return NUMBER[std::stoi(s.substr(0, 1))] + " HUNDRED AND " + transTwo(s.substr(1));
        }
    }

    std::string parseMore(int i) {
        if (i < 0 || i >= static_cast<int>(NUMBER_MORE.size())) {
            throw std::out_of_range("Index out of bounds in parseMore");
        }
        return NUMBER_MORE[i];
    }
};

namespace StringFormatter {
    std::string padLeft(const std::string& s, char c, int length) {
        if (s.length() >= length) {
            return s;
        }
        std::string result = std::string(length - s.length(), c) + s;
        return result;
    }
}