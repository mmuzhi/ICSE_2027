#include <cmath>
#include <iostream>
#include <limits>

class TriCalculator {
public:
    long long factorial(int a) {
        long long result = 1;
        for (int i = 2; i <= a; ++i) {
            result *= i;
        }
        return result;
    }

    double taylor(double x, int n) {
        double angle = x * M_PI / 180.0;
        double result = 1.0;
        int sign = -1;
        for (int k = 1; k < n; ++k) {
            double term = std::pow(angle, 2 * k) / static_cast<double>(factorial(2 * k));
            if (sign == -1) {
                result -= term;
            } else {
                result += term;
            }
            sign *= -1;
        }
        return result;
    }

    double cos(double x) {
        return std::round(taylor(x, 50) * 1e10) / 1e10;
    }

    double sin(double x) {
        double angle = x * M_PI / 180.0;
        double sum = 0.0;
        double term = angle;
        int n = 1;
        while (std::fabs(term) >= 1e-15) {
            sum += term;
            n += 1;
            term = -term * angle * angle / (2 * n - 1) / (2 * n - 2);
        }
        return std::round(sum * 1e10) / 1e10;
    }

    double tan(double x) {
        double cos_val = cos(x);
        if (cos_val == 0.0) {
            return std::numeric_limits<double>::NaN();
        }
        double sin_val = sin(x);
        double result = sin_val / cos_val;
        return std::round(result * 1e10) / 1e10;
    }
};