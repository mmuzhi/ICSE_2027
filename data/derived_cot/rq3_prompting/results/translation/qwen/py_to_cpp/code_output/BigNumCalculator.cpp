#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <cstdlib>

class BigNumCalculator {
public:
    static std::string add(const std::string& num1, const std::string& num2) {
        if (num1.empty() && num2.empty()) return "0";
        if (num1.empty()) return num2;
        if (num2.empty()) return num1;

        int max_length = std::max(num1.size(), num2.size());
        std::string n1 = num1;
        std::string n2 = num2;

        // Pad the shorter string with leading zeros
        if (n1.size() < max_length) {
            n1 = std::string(max_length - n1.size(), '0') + n1;
        }
        if (n2.size() < max_length) {
            n2 = std::string(max_length - n2.size(), '0') + n2;
        }

        int carry = 0;
        std::vector<int> result_digits;
        for (int i = max_length - 1; i >= 0; i--) {
            int digit_sum = (n1[i] - '0') + (n2[i] - '0') + carry;
            carry = digit_sum / 10;
            result_digits.insert(result_digits.begin(), digit_sum % 10);
        }

        if (carry) {
            result_digits.insert(result_digits.begin(), carry);
        }

        // Convert digits to string
        std::string result;
        for (int digit : result_digits) {
            result += ('0' + digit);
        }
        return result;
    }

    static std::string subtract(const std::string& num1, const std::string& num2) {
        if (num1 == num2) return "0";

        // Determine if the result will be negative
        bool negative_result = false;
        if (num1.size() < num2.size()) {
            std::swap(num1, num2);
            negative_result = true;
        } else if (num1.size() == num2.size()) {
            if (num1 < num2) {
                std::swap(num1, num2);
                negative_result = true;
            }
        }

        int max_length = std::max(num1.size(), num2.size());
        std::string n1 = num1;
        std::string n2 = num2;

        // Pad the shorter string with leading zeros
        if (n1.size() < max_length) {
            n1 = std::string(max_length - n1.size(), '0') + n1;
        }
        if (n2.size() < max_length) {
            n2 = std::string(max_length - n2.size(), '0') + n2;
        }

        int borrow = 0;
        std::vector<int> result_digits;
        for (int i = max_length - 1; i >= 0; i--) {
            int digit_diff = (n1[i] - '0') - (n2[i] - '0') - borrow;
            if (digit_diff < 0) {
                digit_diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result_digits.insert(result_digits.begin(), digit_diff);
        }

        // Remove leading zeros
        while (!result_digits.empty() && result_digits.front() == 0) {
            result_digits.erase(result_digits.begin());
        }

        std::string result;
        for (int digit : result_digits) {
            result += ('0' + digit);
        }

        if (negative_result) {
            result = '-' + result;
        }
        return result;
    }

    static std::string multiply(const std::string& num1, const std::string& num2) {
        if (num1.empty() || num2.empty()) return "0";
        if (num1 == "0" || num2 == "0") return "0";

        int len1 = num1.size();
        int len2 = num2.size();
        std::vector<int> result(len1 + len2, 0);

        for (int i = len1 - 1; i >= 0; i--) {
            for (int j = len2 - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j;
                int p2 = i + j + 1;

                int total = mul + result[p2];
                result[p1] += total / 10;
                result[p2] = total % 10;
            }
        }

        // Find the first non-zero digit
        int start = 0;
        while (start < result.size() && result[start] == 0) {
            start++;
        }

        if (start == result.size()) return "0";

        std::string result_str;
        for (int i = start; i < result.size(); i++) {
            result_str += ('0' + result[i]);
        }
        return result_str;
    }
};