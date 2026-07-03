#include <complex>
#include <stdexcept>

class ComplexCalculator {
public:
    static std::complex<double> add(const std::complex<double>& c1, const std::complex<double>& c2) {
        double real = c1.real() + c2.real();
        double imag = c1.imag() + c2.imag();
        return std::complex<double>(real, imag);
    }

    static std::complex<double> subtract(const std::complex<double>& c1, const std::complex<double>& c2) {
        double real = c1.real() - c2.real();
        double imag = c1.imag() - c2.imag();
        return std::complex<double>(real, imag);
    }

    static std::complex<double> multiply(const std::complex<double>& c1, const std::complex<double>& c2) {
        double real = c1.real() * c2.real() - c1.imag() * c2.imag();
        double imag = c1.real() * c2.imag() + c1.imag() * c2.real();
        return std::complex<double>(real, imag);
    }

    static std::complex<double> divide(const std::complex<double>& c1, const std::complex<double>& c2) {
        double denom = c2.real() * c2.real() + c2.imag() * c2.imag();
        if (denom == 0.0) {
            throw std::invalid_argument("Division by zero");
        }
        double real = (c1.real() * c2.real() + c1.imag() * c2.imag()) / denom;
        double imag = (c1.imag() * c2.real() - c1.real() * c2.imag()) / denom;
        return std::complex<double>(real, imag);
    }
};