#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>
#include <stdexcept>

/**
 * This is a class that provides to convert numbers into their corresponding English word representation,
 * including handling the conversion of both the integer and decimal parts, and incorporating appropriate connectors and units.
 */
class NumberWordFormatter {
private:
    std::vector<std::string> NUMBER;
    std::vector<std::string> NUMBER_TEEN;
    std::vector<std::string> NUMBER_TEN;
    std::vector<std::string> NUMBER_MORE;
    std::vector<std::string> NUMBER_SUFFIX;  // NOTE: unused in the original Python code, kept for completeness

public:
    NumberWordFormatter() {
        NUMBER = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
        NUMBER_TEEN = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN",
                       "EIGHTEEN", "NINETEEN"};
        NUMBER_TEN = {"TEN", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
        NUMBER_MORE = {"", "THOUSAND", "MILLION", "BILLION"};
        NUMBER_SUFFIX = {"k", "w", "", "m", "", "", "b", "", "", "t", "", "", "p", "", "", "e"};
    }

    /**
     * Converts a number into words format (string overload).
     * This mimics the Python behaviour: if the argument is not None, it calls format_string(str(x)).
     * For C++ we provide this string version directly.
     */
    std::string format(const std::string& x) {
        return format_string(x);
    }

    /**
     * Converts an integer into words format.
     */
    std::string format(int x) {
        return format_string(std::to_string(x));
    }

    /**
     * Converts a double into words format.
     * Note: std::to_string may not exactly match Python's str(float) for all values.
     * For exact Python behaviour, use format_string() with a pre-formatted string.
     */
    std::string format(double x) {
        return format_string(std::to_string(x));
    }

    /**
     * Converts a string representation of a number into words format.
     */
    std::string format_string(const std::string& x) {
        std::string lstr, rstr;
        size_t dot_pos = x.find('.');
        if (dot_pos != std::string::npos) {
            lstr = x.substr(0, dot_pos);
            rstr = x.substr(dot_pos + 1);
        } else {
            lstr = x;
            rstr = "";
        }

        std::string lstrrev = lstr;
        std::reverse(lstrrev.begin(), lstrrev.end());

        int rem = lstrrev.length() % 3;
        if (rem == 1) {
            lstrrev += "00";
        } else if (rem == 2) {
            lstrrev += "0";
        }

        int num_groups = lstrrev.length() / 3;
        // Python used a = [''] * 5; we use a vector of 5 elements for bounds-checked behaviour.
        std::vector<std::string> a(5, "");
        std::string lm = "";

        for (int i = 0; i < num_groups; ++i) {
            std::string group = lstrrev.substr(3 * i, 3);
            std::reverse(group.begin(), group.end());
            a.at(i) = group;  // throws std::out_of_range if i >= 5, matching Python's IndexError
            if (a[i] != "000") {
                lm = trans_three(a[i]) + " " + parse_more(i) + " " + lm;
            } else {
                lm += trans_three(a[i]);
            }
        }

        std::string xs = "";
        if (!rstr.empty()) {
            xs = "AND CENTS " + trans_two(rstr) + " ";
        }

        // Helper to strip whitespace (mimics Python's str.strip())
        auto strip = [](const std::string& s) -> std::string {
            const char* whitespace = " \t\n\r\f\v";
            size_t start = s.find_first_not_of(whitespace);
            if (start == std::string::npos) return "";
            size_t end = s.find_last_not_of(whitespace);
            return s.substr(start, end - start + 1);
        };

        std::string lm_stripped = strip(lm);
        if (lm_stripped.empty()) {
            return "ZERO ONLY";
        } else {
            return lm_stripped + " " + xs + "ONLY";
        }
    }

    /**
     * Converts a two-digit number into words format.
     */
    std::string trans_two(const std::string& s) {
        std::string padded = s;
        if (padded.length() < 2) {
            padded = std::string(2 - padded.length(), '0') + padded;
        }
        if (padded[0] == '0') {
            return NUMBER[padded.back() - '0'];
        } else if (padded[0] == '1') {
            int val = std::stoi(padded);
            return NUMBER_TEEN.at(val - 10);
        } else if (padded[1] == '0') {
            return NUMBER_TEN.at(padded[0] - '0' - 1);
        } else {
            return NUMBER_TEN.at(padded[0] - '0' - 1) + " " + NUMBER[padded.back() - '0'];
        }
    }

    /**
     * Converts a three-digit number into words format.
     */
    std::string trans_three(const std::string& s) {
        if (s[0] == '0') {
            return trans_two(s.substr(1));
        } else if (s.substr(1) == "00") {
            return NUMBER[s[0] - '0'] + " HUNDRED";
        } else {
            return NUMBER[s[0] - '0'] + " HUNDRED AND " + trans_two(s.substr(1));
        }
    }

    /**
     * Parses the thousand/million/billion suffix based on the index.
     */
    std::string parse_more(int i) {
        return NUMBER_MORE.at(i);
    }
};