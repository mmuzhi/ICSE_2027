#include <cmath>
#include <cstdlib>  // for NAN

class TriCalculator {
private:
    static const double PI;

    double round(double value, int places) {
        double scale = std::pow(10.0, places);
        return std::round(value * scale) / scale;
    }

public:
    TriCalculator() {}

    double cos(double x) {
        return round(taylor(x, 50), 10);
    }

    // kept for interface compatibility (unused internally)
    double factorial(int a) {
        double result = 1.0;
        while (a > 1) {
            result *= a;
            --a;
        }
        return result;
    }

    double taylor(double x, int n) {
        x = x / 180.0 * PI;                       // degrees to radians
        double sum = 1.0;                          // term for k = 0
        double term = 1.0;
        for (int k = 1; k < n; ++k) {
            term = -term * x * x / ((2 * k - 1) * (2 * k));
            sum += term;
        }
        return sum;
    }

    double sin(double x) {
        x = x / 180.0 * PI;
        double g = 0.0;
        double t = x;
        int n = 1;
        while (std::abs(t) >= 1e-15) {
            g += t;
            ++n;
            t = -t * x * x / ((2 * n - 1) * (2 * n - 2));
        }
        return round(g, 10);
    }

    double tan(double x) {
        double cosValue = cos(x);
        if (cosValue != 0.0) {
            return round(sin(x) / cosValue, 10);
        } else {
            return NAN;
        }
    }
};

const double TriCalculator::PI = std::acos(-1.0);