#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class BigNumCalculator {
public:
    static std::string add(std::string num1, std::string num2) {
        int maxLength = std::max((int)num1.length(), (int)num2.length());
        while ((int)num1.length() < maxLength) num1 = "0" + num1;
        while ((int)num2.length() < maxLength) num2 = "0" + num2;

        int carry = 0;
        std::string result;
        for (int i = maxLength - 1; i >= 0; i--) {
            int digitSum = (num1[i] - '0') + (num2[i] - '0') + carry;
            carry = digitSum / 10;
            int digit = digitSum % 10;
            result = (char)('0' + digit) + result;
        }

        if (carry > 0) {
            result = (char)('0' + carry) + result;
        }

        return result;
    }

    static std::string subtract(std::string num1, std::string num2) {
        bool negative = false;
        if (num1.length() < num2.length() || (num1.length() == num2.length() && num1 < num2)) {
            std::swap(num1, num2);
            negative = true;
        }

        int maxLength = std::max((int)num1.length(), (int)num2.length());
        while ((int)num1.length() < maxLength) num1 = "0" + num1;
        while ((int)num2.length() < maxLength) num2 = "0" + num2;

        int borrow = 0;
        std::string result;
        for (int i = maxLength - 1; i >= 0; i--) {
            int digitDiff = (num1[i] - '0') - (num2[i] - '0') - borrow;

            if (digitDiff < 0) {
                digitDiff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result = (char)('0' + digitDiff) + result;
        }

        while (result.length() > 1 && result[0] == '0') {
            result.erase(0, 1);
        }

        if (negative) {
            result = "-" + result;
        }

        return result;
    }

    static std::string multiply(const std::string& num1, const std::string& num2) {
        int len1 = num1.length();
        int len2 = num2.length();
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

        std::string sb;
        int start = 0;
        while (start < (int)result.size() - 1 && result[start] == 0) {
            start++;
        }

        for (int i = start; i < (int)result.size(); i++) {
            sb += (char)('0' + result[i]);
        }

        return sb;
    }
};

int main() {
    std::cout << BigNumCalculator::add("12345678901234567890", "98765432109876543210") << std::endl;
    std::cout << BigNumCalculator::subtract("12345678901234567890", "98765432109876543210") << std::endl;
    std::cout << BigNumCalculator::multiply("12345678901234567890", "98765432109876543210") << std::endl;
    return 0;
}