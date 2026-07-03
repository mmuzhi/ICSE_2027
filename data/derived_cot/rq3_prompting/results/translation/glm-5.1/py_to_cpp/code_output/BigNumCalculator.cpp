#include <string>
#include <vector>
#include <algorithm>

class BigNumCalculator {
public:
    static std::string add(std::string num1, std::string num2) {
        size_t max_length = std::max(num1.length(), num2.length());
        num1 = std::string(max_length - num1.length(), '0') + num1;
        num2 = std::string(max_length - num2.length(), '0') + num2;

        int carry = 0;
        std::vector<std::string> result;
        for (int i = static_cast<int>(max_length) - 1; i >= 0; i--) {
            int digit_sum = (num1[i] - '0') + (num2[i] - '0') + carry;
            carry = digit_sum / 10;
            int digit = digit_sum % 10;
            result.insert(result.begin(), std::to_string(digit));
        }

        if (carry > 0) {
            result.insert(result.begin(), std::to_string(carry));
        }

        std::string s;
        for (const auto& r : result) s += r;
        return s;
    }

    static std::string subtract(std::string num1, std::string num2) {
        bool negative;
        if (num1.length() < num2.length()) {
            std::swap(num1, num2);
            negative = true;
        } else if (num1.length() > num2.length()) {
            negative = false;
        } else {
            if (num1 < num2) {
                std::swap(num1, num2);
                negative = true;
            } else {
                negative = false;
            }
        }

        size_t max_length = std::max(num1.length(), num2.length());
        num1 = std::string(max_length - num1.length(), '0') + num1;
        num2 = std::string(max_length - num2.length(), '0') + num2;

        int borrow = 0;
        std::vector<std::string> result;
        for (int i = static_cast<int>(max_length) - 1; i >= 0; i--) {
            int digit_diff = (num1[i] - '0') - (num2[i] - '0') - borrow;

            if (digit_diff < 0) {
                digit_diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.insert(result.begin(), std::to_string(digit_diff));
        }

        while (result.size() > 1 && result[0] == "0") {
            result.erase(result.begin());
        }

        if (negative) {
            result.insert(result.begin(), "-");
        }

        std::string s;
        for (const auto& r : result) s += r;
        return s;
    }

    static std::string multiply(const std::string& num1, const std::string& num2) {
        int len1 = static_cast<int>(num1.length());
        int len2 = static_cast<int>(num2.length());
        std::vector<int> result(len1 + len2, 0);

        for (int i = len1 - 1; i >= 0; i--) {
            for (int j = len2 - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int total = mul + result[p2];

                result[p1] += total / 10;
                result[p2] = total % 10;
            }
        }

        int start = 0;
        while (start < static_cast<int>(result.size()) - 1 && result[start] == 0) {
            start++;
        }

        std::string s;
        for (int i = start; i < static_cast<int>(result.size()); i++) {
            s += std::to_string(result[i]);
        }
        return s;
    }
};