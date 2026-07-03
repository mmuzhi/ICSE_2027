#include <string>
#include <vector>
#include <algorithm>
#include <cstddef>

class BigNumCalculator {
public:
    static std::string add(const std::string& num1, const std::string& num2) {
        size_t max_len = std::max(num1.length(), num2.length());
        std::string a = std::string(max_len - num1.length(), '0') + num1;
        std::string b = std::string(max_len - num2.length(), '0') + num2;

        int carry = 0;
        std::string result;
        for (int i = static_cast<int>(max_len) - 1; i >= 0; --i) {
            int digit_sum = (a[i] - '0') + (b[i] - '0') + carry;
            carry = digit_sum / 10;
            int digit = digit_sum % 10;
            result = char('0' + digit) + result;
        }
        if (carry > 0) {
            result = char('0' + carry) + result;
        }
        return result;
    }

    static std::string subtract(const std::string& num1, const std::string& num2) {
        std::string a = num1;
        std::string b = num2;
        bool negative = false;

        if (a.length() < b.length()) {
            std::swap(a, b);
            negative = true;
        } else if (a.length() == b.length() && a < b) {
            std::swap(a, b);
            negative = true;
        }

        size_t max_len = std::max(a.length(), b.length());
        a = std::string(max_len - a.length(), '0') + a;
        b = std::string(max_len - b.length(), '0') + b;

        int borrow = 0;
        std::string result;
        for (int i = static_cast<int>(max_len) - 1; i >= 0; --i) {
            int digit_diff = (a[i] - '0') - (b[i] - '0') - borrow;
            if (digit_diff < 0) {
                digit_diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result = char('0' + digit_diff) + result;
        }

        // Remove leading zeros
        while (result.length() > 1 && result[0] == '0') {
            result.erase(result.begin());
        }

        if (negative) {
            result = '-' + result;
        }
        return result;
    }

    static std::string multiply(const std::string& num1, const std::string& num2) {
        size_t len1 = num1.length();
        size_t len2 = num2.length();
        std::vector<int> result(len1 + len2, 0);

        for (int i = static_cast<int>(len1) - 1; i >= 0; --i) {
            for (int j = static_cast<int>(len2) - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j;
                int p2 = i + j + 1;
                int total = mul + result[p2];
                result[p1] += total / 10;
                result[p2] = total % 10;
            }
        }

        // Skip leading zeros
        size_t start = 0;
        while (start < result.size() - 1 && result[start] == 0) {
            ++start;
        }

        std::string out;
        for (size_t k = start; k < result.size(); ++k) {
            out += char('0' + result[k]);
        }
        return out;
    }
};