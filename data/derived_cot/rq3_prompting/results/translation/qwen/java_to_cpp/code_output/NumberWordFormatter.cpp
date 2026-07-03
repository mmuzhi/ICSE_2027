#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>

class NumberWordFormatter {
private:
    std::vector<std::string> NUMBER = { "", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE" };
    std::vector<std::string> NUMBER_TEEN = { "TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN" };
    std::vector<std::string> NUMBER_TEN = { "TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY" };
    std::vector<std::string> NUMBER_MORE = { "", "THOUSAND", "MILLION", "BILLION" };

    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    std::string transTwo(const std::string& s) {
        if (s.length() == 1) {
            s = "0" + s;
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
        } else if (s.length() == 3 && s[1] == '0' && s[2] == '0') {
            return NUMBER[std::stoi(s.substr(0, 1))] + " HUNDRED";
        } else {
            return NUMBER[std::stoi(s.substr(0, 1))] + " HUNDRED AND " + transTwo(s.substr(1));
        }
    }

    std::string parseMore(int i) {
        if (i < 0 || i >= NUMBER_MORE.size()) {
            return "";
        }
        return NUMBER_MORE[i];
    }

public:
    std::string format(const std::string& x) {
        if (x.empty()) {
            return "";
        }
        return formatString(x);
    }

    std::string formatString(const std::string& x) {
        std::stringstream ss(x);
        std::string part;
        std::vector<std::string> parts;
        while (std::getline(ss, part, '.')) {
            parts.push_back(part);
        }

        std::string lstr = parts[0];
        std::string rstr = parts.size() > 1 ? parts[1] : "";
        std::string lstrrev = std::string(lstr.rbegin(), lstr.rend());

        if (lstr.empty()) {
            return "ZERO ONLY";
        }

        if (lstrrev.length() % 3 == 1) {
            lstrrev += "00";
        } else if (lstrrev.length() % 3 == 2) {
            lstrrev += "0";
        }

        std::string leftPart;
        for (int i = 0; i < lstrrev.length() / 3; i++) {
            std::string chunk = lstrrev.substr(3 * i, 3);
            std::string reversed_chunk = std::string(chunk.rbegin(), chunk.rend());
            if (reversed_chunk != "000") {
                std::string group = transThree(reversed_chunk) + " " + parseMore(i);
                if (!leftPart.empty()) {
                    leftPart = group + " " + leftPart;
                } else {
                    leftPart = group;
                }
            }
        }

        std::string rightPart;
        if (!rstr.empty()) {
            rightPart = "AND CENTS " + transTwo(rstr) + " ";
        }

        std::string fullString = trim(leftPart) + " " + trim(rightPart);
        if (fullString.empty()) {
            return "ZERO ONLY";
        } else {
            return fullString + "ONLY";
        }
    }
};

int main() {
    NumberWordFormatter formatter;
    std::cout << formatter.format("123.45") << std::endl;
    return 0;
}