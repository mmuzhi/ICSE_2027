#include <cmath>
#include <limits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class TriCalculator {

public:
    taylor() {}

    double cos(double x) {
        x = x * M_PI / 180.0;
        double term = 1.0;
        double result = 1.0;
        int count = 1;
        for (int k = 1; k < 50; k++) {
            term = term * (-x*x) / ((2*k)*(2*k-1));
            result += term;
            count++;
        }
        return round(result, 10);
    }

    double sin(double x) {
        x = x * M_PI / 180.0;
        double g = 0;
        double t = x;
        int n = 1;

        while (std::abs(t) >= 1e-15) {
            g += t;
            n += 1;
            t = -t * x * x / ((2*n-1)*(2*n-2));
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

private:
    double round(double value, int places) {
        double factor = std::pow(10.0, places);
        return std::round(value * factor) / factor;
    }
};