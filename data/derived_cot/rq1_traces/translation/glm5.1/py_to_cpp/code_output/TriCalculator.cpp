#include <cmath>

// Define M_PI if not available (e.g., MSVC)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class TriCalculator {
public:
    TriCalculator() {}

    double cos(double x) {
        return round_to(taylor(x, 50), 10);
    }

    // Note: Python's integers have arbitrary precision, so factorial(98) is exact.
    // In C++, unsigned long long overflows at 21!. To match the numerical output 
    // of the Taylor series without using an external big-integer library, 
    // we use double which can hold up to ~1.8e308 without overflow, 
    // though with some floating-point precision loss.
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
        x = x / 180.0 * M_PI;
        int count = 1;
        for (int k = 1; k < n; ++k) {
            if (count % 2 != 0) {
                a -= std::pow(x, 2 * k) / factorial(2 * k);
            } else {
                a += std::pow(x, 2 * k) / factorial(2 * k);
            }
            count++;
        }
        return a;
    }

    double sin(double x) {
        x = x / 180.0 * M_PI;
        double g = 0;
        double t = x;
        int n = 1;

        while (std::fabs(t) >= 1e-15) {
            g += t;
            n += 1;
            t = -t * x * x / (2 * n - 1) / (2 * n - 2);
        }
        return round_to(g, 10);
    }

    // Note: Python's tan() returns False when cos(x) == 0. 
    // In C++, returning 0.0 behaves identically to Python's False in 
    // boolean contexts and arithmetic operations (since False == 0 in Python).
    double tan(double x) {
        if (cos(x) != 0) {
            double result = sin(x) / cos(x);
            return round_to(result, 10);
        } else {
            return 0.0; 
        }
    }

private:
    // Helper function to mimic Python's round(x, n) which rounds to n decimal places
    static double round_to(double val, int decimal_places) {
        double multiplier = std::pow(10.0, decimal_places);
        return std::round(val * multiplier) / multiplier;
    }
};