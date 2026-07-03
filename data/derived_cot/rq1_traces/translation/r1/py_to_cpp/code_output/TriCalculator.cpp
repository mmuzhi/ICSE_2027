#include <cmath>
#include <limits>

const double PI = 3.14159265358979323846;

class TriCalculator {
public:
    TriCalculator() {}

    double cos(double x);
    double sin(double x);
    double tan(double x);
    double factorial(int a);
    double taylor(double x, int n);
};

double TriCalculator::factorial(int a) {
    if (a == 0) {
        return 1.0;
    }
    double b = 1.0;
    while (a > 1) {
        b *= a;
        a--;
    }
    return b;
}

double TriCalculator::taylor(double x, int n) {
    double a = 1.0;
    x = x / 180.0 * PI;
    int count = 1;
    for (int k = 1; k < n; k++) {
        double exponent = 2 * k;
        double term = std::pow(x, exponent) / factorial(static_cast<int>(exponent));
        if (count % 2 != 0) {
            a -= term;
        } else {
            a += term;
        }
        count++;
    }
    return a;
}

double TriCalculator::cos(double x) {
    double result = taylor(x, 50);
    result = std::round(result * 1e10) / 1e10;
    return result;
}

double TriCalculator::sin(double x) {
    x = x / 180.0 * PI;
    double g = 0.0;
    double t = x;
    int n = 1;

    while (std::fabs(t) >= 1e-15) {
        g += t;
        n++;
        t = -t * x * x / ((2.0 * n - 1.0) * (2.0 * n - 2.0));
    }
    g = std::round(g * 1e10) / 1e10;
    return g;
}

double TriCalculator::tan(double x) {
    double c = cos(x);
    if (c == 0.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double s = sin(x);
    double result = s / c;
    result = std::round(result * 1e10) / 1e10;
    return result;
}