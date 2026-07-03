#include <string>
#include <vector>
#include <algorithm>

class BigNumCalculator {
public:
    static std::string add(const std::string& num1, const std::string& num2) {
        int max_length = std::max(num1.size(), num2.size());
        std::string a = num1;
        std::string b = num2;
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());
        
        a = std::string(max_length - a.size(), '0') + a;
        b = std::string(max_length - b.size(), '0') + b;

        int carry = 0;
        std::vector<int> digits;
        for (int i = 0; i < max_length; ++i) {
            int digit_sum = (a[i] - '0') + (b[i] - '0') + carry;
            carry = digit_sum / 10;
            digits.push_back(digit_sum % 10);
        }
        if (carry) {
            digits.push_back(carry);
        }

        std::reverse(digits.begin(), digits.end());
        std::string result;
        for (int digit : digits) {
            result += ('0' + digit);
        }
        return result;
    }

    static std::string subtract(const std::string& num1, const std::string& num2) {
        int len1 = num1.size();
        int len2 = num2.size();
        int max_length = std::max(len1, len2);
        std::string a = num1;
        std::string b = num2;
        std::reverse(a.begin(), a.end());
        std::reverse(b.begin(), b.end());
        
        a = std::string(max_length - len1, '0') + a;
        b = std::string(max_length - len2, '0') + b;

        bool negative = false;
        if (a < b) {
            std::swap(a, b);
            negative = true;
        }

        int borrow = 0;
        std::vector<int> digits;
        for (int i = 0; i < max_length; ++i) {
            int digit_diff = (a[i] - '0') - (b[i] - '0') - borrow;
            if (digit_diff < 0) {
                digit_diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            digits.push_back(digit_diff);
        }

        std::reverse(digits.begin(), digits.end());
        std::string result;
        for (int digit : digits) {
            result += ('0' + digit);
        }

        if (negative && !result.empty()) {
            if (result[0] != '0') {
                result = '-' + result;
            } else {
                result = result.substr(1);
            }
        }
        return result;
    }

    static std::string multiply(const std::string& num1, const std::string& num2) {
        int len1 = num1.size();
        int len2 = num2.size();
        std::vector<int> result(len1 + len2, 0);

        for (int i = 0; i < len1; ++i) {
            for (int j = 0; j < len2; ++j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int pos1 = i + j;
                int pos2 = i + j + 1;
                int total = mul + result[pos2];
                result[pos1] += total / 10;
                result[pos2] = total % 10;
            }
        }

        int start = 0;
        while (start < result.size() - 1 && result[start] == 0) {
            ++start;
        }

        std::string res;
        for (int i = start; i < result.size(); ++i) {
            res += ('0' + result[i]);
        }
        return res;
    }
};