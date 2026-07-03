#define _USE_MATH_DEFINES
#include <cmath>
#include <boost/multiprecision/cpp_dec_float.hpp>

using Decimal = boost::multiprecision::cpp_dec_float_50;

class TriCalculator {
public:
    TriCalculator() {}

    double cos(double x) {
        return round(taylor(x, 50), 10);
    }

    Decimal factorial(int a) {
        Decimal result = Decimal(1);
        while (a > 1) {
            result *= a;
            a--;
        }
        return result;
    }

    double taylor(double x, int n) {
        x = x / 180 * M_PI;
        Decimal a = Decimal(1);
        int count = 1;
        for (int k = 1; k < n; k++) {
            double term_double = std::pow(x, 2 * k);
            Decimal term = Decimal(term_double) / factorial(2 * k);
            if (count % 2 != 0) {
                a -= term;
            } else {
                a += term;
            }
            count++;
        }
        return a.convert_to<double>();
    }

    double sin(double x) {
        x = x / 180 * M_PI;
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
            return NAN;
        }
    }

private:
    double round(double value, int places) {
        double multiplier = std::pow(10.0, places);
        double shifted = value * multiplier;
        if (value >= 0) {
            shifted = std::floor(shifted + 0.5);
        } else {
            shifted = std::ceil(shifted - 0.5);
        }
        return shifted / multiplier;
    }
};