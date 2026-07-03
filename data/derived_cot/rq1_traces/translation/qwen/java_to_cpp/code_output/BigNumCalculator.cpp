#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>

class BigNumCalculator {
public:
    static std::string add(const std::string& num1, const std::string& num2) {
        int maxLength = std::max(num1.size(), num2.size());
        std::string num1Padded = std::string(maxLength - num1.size(), '0') + num1;
        std::string num2Padded = std::string(maxLength - num2.size(), '0') + num2;

        int carry = 0;
        std::string result = "";

        for (int i = maxLength - 1; i >= 0; i--) {
            int digitSum = (num1Padded[i] - '0') + (num2Padded[i] - '0') + carry;
            carry = digitSum / 10;
            int digit = digitSum % 10;
            result = char(digit + '0') + result;
        }

        if (carry) {
            result = char(carry + '0') + result;
        }

        return result;
    }

    static std::string subtract(const std::string& num1, const std::string& num2) {
        if (num1 == num2) {
            return "0";
        }

        bool negative = false;
        if (num1.size() < num2.size() || (num1.size() == num2.size() && num1 < num2)) {
            std::swap(num1, num2);
            negative = true;
        }

        int maxLength = std::max(num1.size(), num2.size());
        std::string num1Padded = std::string(maxLength - num1.size(), '0') + num1;
        std::string num2Padded = std::string(maxLength - num2.size(), '0') + num2;

        int borrow = 0;
        std::string result = "";

        for (int i = maxLength - 1; i >= 0; i--) {
            int digitDiff = (num1Padded[i] - '0') - (num2Padded[i] - '0') - borrow;
            if (digitDiff < 0) {
                digitDiff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result = char(digitDiff + '0') + result;
        }

        while (result.size() > 1 && result[0] == '0') {
            result.erase(0, 1);
        }

        if (negative) {
            result = '-' + result;
        }

        return result;
    }

    static std::string multiply(const std::string& num1, const std::string& num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }

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

        std::string finalResult = "";
        int start = 0;
        while (start < result.size() - 1 && result[start] == 0) {
            start++;
        }

        for (int i = start; i < result.size(); i++) {
            finalResult += char(result[i] + '0');
        }

        return finalResult;
    }

    static void main() {
        std::cout << add("12345678901234567890", "98765432109876543210") << std::endl;
        std::cout << subtract("12345678901234567890", "98765432109876543210") << std::endl;
        std::cout << multiply("12345678901234567890", "98765432109876543210") << std::endl;
    }
};

int main() {
    BigNumCalculator::main();
    return 0;
}