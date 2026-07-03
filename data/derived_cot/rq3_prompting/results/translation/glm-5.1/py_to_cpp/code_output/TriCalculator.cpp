#include <cmath>

class TriCalculator {
public:
    TriCalculator() {}

    double cos(double x) {
        return std::round(taylor(x, 50) * 1e10) / 1e10;
    }

    double factorial(int a) {
        double b = 1;
        while (a != 1) {
            b *= a;
            a -= 1;
        }
        return b;
    }

    double taylor(double x, int n) {
        double a = 1;
        x = x / 180 * M_PI;
        int count = 1;
        for (int k = 1; k < n; ++k) {
            if (count % 2 != 0) {
                a -= std::pow(x, 2 * k) / factorial(2 * k);
            } else {
                a += std::pow(x, 2 * k) / factorial(2 * k);
            }
            count += 1;
        }
        return a;
    }

    double sin(double x) {
        x = x / 180 * M_PI;
        double g = 0;
        double t = x;
        int n = 1;

        while (std::fabs(t) >= 1e-15) {
            g += t;
            n += 1;
            t = -t * x * x / (2 * n - 1) / (2 * n - 2);
        }
        return std::round(g * 1e10) / 1e10;
    }

    double tan(double x) {
        if (cos(x) != 0) {
            double result = sin(x) / cos(x);
            return std::round(result * 1e10) / 1e10;
        } else {
            return false; // false implicitly converts to 0.0, matching Python's False
        }
    }
};