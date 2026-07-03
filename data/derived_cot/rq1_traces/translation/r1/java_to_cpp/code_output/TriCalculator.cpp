#include <cmath>
#include <iostream>

class TriCalculator {
private:
    const double PI = 3.14159265358979323846;

    double round(double value, int places) {
        double factor = std::pow(10.0, places);
        return std::round(value * factor) / factor;
    }

public:
    TriCalculator() {}

    double cos(double x) {
        double x_rad = x * PI / 180.0;
        int n = 50;
        double result = 1.0;
        double term = 1.0;
        for (int k = 1; k < n; k++) {
            term = term * (-1) * (x_rad * x_rad) / ((2 * k - 1) * (2 * k));
            result += term;
        }
        return round(result, 10);
    }

    double sin(double x) {
        double x_rad = x * PI / 180.0;
        double g = 0;
        double t = x_rad;
        int n = 1;

        while (std::fabs(t) >= 1e-15) {
            g += t;
            n++;
            t = -t * x_rad * x_rad / ((2 * n - 1) * (2 * n - 2));
        }
        return round(g, 10);
    }

    double tan(double x) {
        double cosValue = cos(x);
        if (cosValue != 0.0) {
            double sinValue = sin(x);
            return round(sinValue / cosValue, 10);
        } else {
            return std::nan("");
        }
    }
};