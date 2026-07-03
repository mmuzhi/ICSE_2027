#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class BigNumCalculator {
public:
    static std::string add(const std::string& num1, const std::string& num2) {
        size_t maxLen = std::max(num1.length(), num2.length());
        std::string a(maxLen - num1.length(), '0');
        a += num1;
        std::string b(maxLen - num2.length(), '0');
        b += num2;

        int carry = 0;
        std::string result;
        for (int i = static_cast<int>(maxLen) - 1; i >= 0; --i) {
            int digitSum = (a[i] - '0') + (b[i] - '0') + carry;
            carry = digitSum / 10;
            int digit = digitSum % 10;
            result.insert(result.begin(), static_cast<char>('0' + digit));
        }
        if (carry > 0) {
            result.insert(result.begin(), static_cast<char>('0' + carry));
        }
        return result;
    }

    static std::string subtract(const std::string& num1, const std::string& num2) {
        bool negative = false;
        std::string n1 = num1;
        std::string n2 = num2;
        if (n1.length() < n2.length() || (n1.length() == n2.length() && n1 < n2)) {
            std::swap(n1, n2);
            negative = true;
        }

        size_t maxLen = std::max(n1.length(), n2.length());
        std::string a(maxLen - n1.length(), '0');
        a += n1;
        std::string b(maxLen - n2.length(), '0');
        b += n2;

        int borrow = 0;
        std::string result;
        for (int i = static_cast<int>(maxLen) - 1; i >= 0; --i) {
            int digitDiff = (a[i] - '0') - (b[i] - '0') - borrow;
            if (digitDiff < 0) {
                digitDiff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.insert(result.begin(), static_cast<char>('0' + digitDiff));
        }

        // Remove leading zeros (keep at least one digit)
        size_t pos = result.find_first_not_of('0');
        if (pos != std::string::npos) {
            result = result.substr(pos);
        } else {
            result = "0";
        }

        if (negative && result != "0") {
            result.insert(result.begin(), '-');
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

        std::string sb;
        size_t start = 0;
        while (start < result.size() - 1 && result[start] == 0) {
            ++start;
        }
        for (size_t i = start; i < result.size(); ++i) {
            sb.push_back(static_cast<char>('0' + result[i]));
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