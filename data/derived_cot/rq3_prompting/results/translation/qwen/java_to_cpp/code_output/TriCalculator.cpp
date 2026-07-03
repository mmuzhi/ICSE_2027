#include <cmath>
#include <limits>

class TriCalculator {
public:
    TriCalculator() = default;

    double cos(double x) {
        double radians = x * M_PI / 180.0;
        double sum = 1.0;
        double term = 1.0;
        int count = 1;

        for (int k = 1; k < 50; ++k) {
            term *= radians * radians;
            term /= (2.0 * k * (2.0 * k - 1.0));
            if (count % 2 != 0) {
                sum -= term;
            } else {
                sum += term;
            }
            count++;
        }

        return round(sum, 10);
    }

    double sin(double x) {
        double radians = x * M_PI / 180.0;
        double sum = 0.0;
        double term = radians;
        int n = 1;

        while (std::abs(term) >= 1e-15) {
            sum += term;
            n++;
            term = -term * radians * radians / ((2.0 * n - 1.0) * (2.0 * n - 2.0));
        }

        return round(sum, 10);
    }

    double tan(double x) {
        double sinValue = sin(x);
        double cosValue = cos(x);

        if (cosValue == 0) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        return round(sinValue / cosValue, 10);
    }

private:
    double round(double value, int places) {
        if (places < 0) {
            return std::round(value);
        }

        double scale = std::pow(10.0, places);
        return std::round(value * scale) / scale;
    }
};