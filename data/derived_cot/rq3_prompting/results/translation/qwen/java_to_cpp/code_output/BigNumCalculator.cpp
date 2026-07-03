#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

class BigNumCalculator {

public:
    static std::string add(const std::string& num1, const std::string& num2) {
        int maxLength = std::max(num1.length(), num2.length());
        std::string paddedNum1 = std::string(maxLength - num1.length(), '0') + num1;
        std::string paddedNum2 = std::string(maxLength - num2.length(), '0') + num2;

        int carry = 0;
        std::string result;
        for (int i = maxLength - 1; i >= 0; i--) {
            int digitSum = (paddedNum1[i] - '0') + (paddedNum2[i] - '0') + carry;
            carry = digitSum / 10;
            result = char(digitSum % 10 + '0') + result;
        }

        if (carry) {
            result = char(carry + '0') + result;
        }

        return result;
    }

    static std::string subtract(const std::string& num1, const std::string& num2) {
        bool negative = false;
        if (num1.length() < num2.length() || 
            (num1.length() == num2.length() && num1 < num2)) {
            std::swap(num1, num2);
            negative = true;
        }

        int maxLength = std::max(num1.length(), num2.length());
        std::string paddedNum1 = std::string(maxLength - num1.length(), '0') + num1;
        std::string paddedNum2 = std::string(maxLength - num2.length(), '0') + num2;

        int borrow = 0;
        std::string result;
        for (int i = maxLength - 1; i >= 0; i--) {
            int digitDiff = (paddedNum1[i] - '0') - (paddedNum2[i] - '0') - borrow;
            if (digitDiff < 0) {
                digitDiff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result = char(digitDiff + '0') + result;
        }

        // Remove leading zeros
        size_t start = 0;
        while (start < result.length() - 1 && result[start] == '0') {
            start++;
        }
        result = result.substr(start);

        if (negative) {
            result = '-' + result;
        }

        return result;
    }

    static std::string multiply(const std::string& num1, const std::string& num2) {
        int len1 = num1.length(), len2 = num2.length();
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
        size_t start = 0;
        while (start < result.size() && result[start] == 0) {
            start++;
        }

        std::string res;
        for (int i = start; i < result.size(); i++) {
            res += char(result[i] + '0');
        }

        return res;
    }
};

#include <iostream>
using namespace std;

int main() {
    cout << BigNumCalculator::add("12345678901234567890", "98765432109876543210") << endl;
    cout << BigNumCalculator::subtract("12345678901234567890", "98765432109876543210") << endl;
    cout << BigNumCalculator::multiply("12345678901234567890", "98765432109876543210") << endl;
    return 0;
}