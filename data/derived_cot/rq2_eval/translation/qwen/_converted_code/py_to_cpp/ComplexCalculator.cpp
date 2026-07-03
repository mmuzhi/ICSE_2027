#include <complex>

class ComplexCalculator {
public:
    static std::complex<double> add(const std::complex<double>& c1, const std::complex<double>& c2) {
        return c1 + c2;
    }

    static std::complex<double> subtract(const std::complex<double>& c1, const std::complex<double>& c2) {
        return c1 - c2;
    }

    static std::complex<double> multiply(const std::complex<double>& c1, const std::complex<double>& c2) {
        return c1 * c2;
    }

    static std::complex<double> divide(const std::complex<double>& c1, const std::complex<double>& c2) {
        return c1 / c2;
    }
};