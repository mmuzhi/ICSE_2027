#include <cmath>
#include <limits>

class TriCalculator {
private:
    static constexpr double PI = 3.14159265358979323846;

    double round(double value, int places) {
        double multiplier = std::pow(10.0, places);
        // std::floor(x + 0.5) accurately mimics Java's BigDecimal RoundingMode.HALF_UP 
        // for both positive and negative doubles when operating on the exact binary value.
        return std::floor(value * multiplier + 0.5) / multiplier;
    }

public:
    TriCalculator() {}

    double cos(double x) {
        return round(taylor(x, 50), 10);
    }

    double factorial(int a) {
        double result = 1.0;
        while (a > 1) {
            result *= a;
            a--;
        }
        return result;
    }

    double taylor(double x, int n) {
        double a = 1.0;
        x = x / 180 * PI;
        int count = 1;
        for (int k = 1; k < n; k++) {
            double term = std::pow(x, 2 * k) / factorial(2 * k);
            if (count % 2 != 0) {
                a = a - term;
            } else {
                a = a + term;
            }
            count++;
        }
        return a;
    }

    double sin(double x) {
        x = x / 180 * PI;
        double g = 0;
        double t = x;
        int n = 1;

        while (std::abs(t) >= 1e-15) {
            g += t;
            n += 1;
            t = -t * x * x / (2 * n - 1) / (2 * n - 2);
        }
        return round(g, 10);
    }

    double tan(double x) {
        double cosValue = cos(x);
        if (cosValue != 0) {
            return round(sin(x) / cosValue, 10);
        } else {
            return std::numeric_limits<double>::quiet_NaN();
        }
    }
};