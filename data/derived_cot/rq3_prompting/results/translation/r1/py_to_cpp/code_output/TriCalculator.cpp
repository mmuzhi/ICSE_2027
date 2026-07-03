#include <cmath>
#include <limits>

const double PI = std::acos(-1.0);

class TriCalculator {
public:
    TriCalculator() = default;

    double cos(double x) {
        double raw = taylor(x, 50);
        return std::round(raw * 1e10) / 1e10;
    }

    double factorial(int a) {
        double result = 1.0;
        while (a != 1) {
            result *= a;
            a -= 1;
        }
        return result;
    }

    double taylor(double x, int n) {
        double a = 1.0;
        x = x / 180.0 * PI;
        int count = 1;
        for (int k = 1; k < n; ++k) {
            if (count % 2 != 0) {
                a -= std::pow(x, 2 * k) / factorial(2 * k);
            } else {
                a += std::pow(x, 2 * k) / factorial(2 * k);
            }
            ++count;
        }
        return a;
    }

    double sin(double x) {
        x = x / 180.0 * PI;
        double g = 0.0;
        double t = x;
        int n = 1;
        while (std::fabs(t) >= 1e-15) {
            g += t;
            ++n;
            t = -t * x * x / (2 * n - 1) / (2 * n - 2);
        }
        return std::round(g * 1e10) / 1e10;
    }

    double tan(double x) {
        double cos_val = cos(x);
        if (cos_val != 0.0) {
            double result = sin(x) / cos_val;
            return std::round(result * 1e10) / 1e10;
        } else {
            return std::numeric_limits<double>::quiet_NaN();
        }
    }
};