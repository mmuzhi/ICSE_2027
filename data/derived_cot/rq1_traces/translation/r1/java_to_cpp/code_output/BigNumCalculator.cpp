#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::string add(const std::string& num1, const std::string& num2) {
    int maxLength = std::max(num1.size(), num2.size());
    std::string n1 = num1;
    std::string n2 = num2;
    if (n1.size() < maxLength) {
        n1 = std::string(maxLength - n1.size(), '0') + n1;
    }
    if (n2.size() < maxLength) {
        n2 = std::string(maxLength - n2.size(), '0') + n2;
    }

    int carry = 0;
    std::string result;
    for (int i = maxLength - 1; i >= 0; i--) {
        int digitSum = (n1[i] - '0') + (n2[i] - '0') + carry;
        carry = digitSum / 10;
        int digit = digitSum % 10;
        result.push_back('0' + digit);
    }

    if (carry > 0) {
        result.push_back('0' + carry);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

std::string subtract(const std::string& num1, const std::string& num2) {
    std::string n1 = num1;
    std::string n2 = num2;
    bool negative = false;

    if (n1.size() < n2.size() || (n1.size() == n2.size() && n1 < n2)) {
        std::swap(n1, n2);
        negative = true;
    }

    int maxLength = std::max(n1.size(), n2.size());
    if (n1.size() < maxLength) {
        n1 = std::string(maxLength - n1.size(), '0') + n1;
    }
    if (n2.size() < maxLength) {
        n2 = std::string(maxLength - n2.size(), '0') + n2;
    }

    int borrow = 0;
    std::string result;
    for (int i = maxLength - 1; i >= 0; i--) {
        int digitDiff = (n1[i] - '0') - (n2[i] - '0') - borrow;
        if (digitDiff < 0) {
            digitDiff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.push_back('0' + digitDiff);
    }

    std::reverse(result.begin(), result.end());

    size_t start = 0;
    while (start < result.size() - 1 && result[start] == '0') {
        start++;
    }
    result = result.substr(start);

    if (negative) {
        result = '-' + result;
    }

    return result;
}

std::string multiply(const std::string& num1, const std::string& num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    std::vector<int> result(len1 + len2, 0);

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int p1 = i + j;
            int p2 = i + j + 1;
            int total = mul + result[p2];
            result[p2] = total % 10;
            result[p1] += total / 10;
        }
    }

    std::string sb;
    int start = 0;
    while (start < result.size() - 1 && result[start] == 0) {
        start++;
    }
    for (int i = start; i < result.size(); i++) {
        sb += ('0' + result[i]);
    }
    return sb;
}

int main() {
    std::cout << add("12345678901234567890", "98765432109876543210") << std::endl;
    std::cout << subtract("12345678901234567890", "98765432109876543210") << std::endl;
    std::cout << multiply("12345678901234567890", "98765432109876543210") << std::endl;
    return 0;
}