#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BigNumCalculator {
public:
    static string add(string num1, string num2) {
        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int carry = 0;
        string result = "";

        while (i >= 0 || j >= 0 || carry) {
            int d1 = (i >= 0) ? num1[i] - '0' : 0;
            int d2 = (j >= 0) ? num2[j] - '0' : 0;
            if (i >= 0) i--;
            if (j >= 0) j--;
            int total = d1 + d2 + carry;
            carry = total / 10;
            result.push_back(total % 10 + '0');
        }

        reverse(result.begin(), result.end());
        return result;
    }

    static string subtract(string num1, string num2) {
        bool negative = false;
        if (num1.size() < num2.size() || (num1.size() == num2.size() && num1 < num2)) {
            negative = true;
            swap(num1, num2);
        }

        int i = num1.size() - 1;
        int j = num2.size() - 1;
        int borrow = 0;
        string result = "";

        while (i >= 0 || j >= 0) {
            int d1 = (i >= 0) ? num1[i] - '0' : 0;
            int d2 = (j >= 0) ? num2[j] - '0' : 0;
            if (i >= 0) i--;
            if (j >= 0) j--;
            int diff = d1 - d2 - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff + '0');
        }

        reverse(result.begin(), result.end());

        int start = 0;
        while (start < result.size() - 1 && result[start] == '0') {
            start++;
        }
        result = result.substr(start);

        if (negative) {
            result = "-" + result;
        }
        return result;
    }

    static string multiply(string num1, string num2) {
        int len1 = num1.size();
        int len2 = num2.size();
        vector<int> result(len1 + len2, 0);

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

        int start = 0;
        while (start < result.size() - 1 && result[start] == 0) {
            start++;
        }

        string res_str = "";
        for (int i = start; i < result.size(); i++) {
            res_str += (result[i] + '0');
        }
        return res_str;
    }
};