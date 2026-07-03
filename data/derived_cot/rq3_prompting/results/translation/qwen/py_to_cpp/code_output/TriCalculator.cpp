#include <cmath>
#include <iostream>
#include <limits>

class TriCalculator {
public:
    TriCalculator() {}

    int factorial(int a) {
        int result = 1;
        for (int i = 2; i <= a; ++i) {
            result *= i;
        }
        return result;
    }

    double taylor(float x, int n) {
        double a = 1.0;
        double x_rad = x / 180.0 * M_PI;
        int count = 1;
        for (int k = 1; k < n; ++k) {
            if (count % 2 != 0) {
                a -= std::pow(x_rad, 2 * k) / factorial(2 * k);
            } else {
                a += std::pow(x_rad, 2 * k) / factorial(2 * k);
            }
            ++count;
        }
        return a;
    }

    double cos(float x) {
        double result = taylor(x, 50);
        return std::round(result * 1e10) / 1e10;
    }

    double sin(float x) {
        x = x / 180.0 * M_PI;
        double g = 0.0;
        double t = x;
        int n = 1;

        while (std::fabs(t) >= 1e-15) {
            g += t;
            n += 1;
            t = -t * x * x / ((2 * n - 1) * (2 * n - 2));
        }
        return std::round(g * 1e10) / 1e10;
    }

    double tan(float x) {
        if (cos(x) == 0.0) {
            return 0.0 / 0.0; // Return NaN for undefined result
        }
        return std::round(sin(x) / cos(x) * 1e10) / 1e10;
    }
};