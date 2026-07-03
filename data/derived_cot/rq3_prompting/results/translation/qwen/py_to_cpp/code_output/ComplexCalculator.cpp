#include <complex>
#include <stdexcept>

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
        if (c2.real() == 0.0 && c2.imag() == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        return c1 / c2;
    }
};