#include <cmath>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdint>
#include <type_traits>

// Mimics Java's Double.compare exactly, handling NaN and -0.0
inline int double_compare(double a, double b) {
    if (std::isnan(a) && std::isnan(b)) return 0;        // NaN == NaN
    if (a != a) return 1;                                 // a is NaN, b is not -> greater (Java spec)
    if (b != b) return -1;                                // b is NaN, a is not -> less
    if (a == b) {
        // Distinguish +0.0 and -0.0
        if (a == 0.0) {
            // Both zeros, compare sign bits
            return (std::signbit(a) == std::signbit(b)) ? 0 : (std::signbit(a) ? -1 : 1);
        }
        return 0;
    }
    return (a < b) ? -1 : 1;
}

class ComplexNumber {
public:
    ComplexNumber(double real, double imaginary) : real_(real), imag_(imaginary) {}

    double getReal() const { return real_; }
    double getImaginary() const { return imag_; }

    bool operator==(const ComplexNumber& other) const {
        return double_compare(real_, other.real_) == 0 &&
               double_compare(imag_, other.imag_) == 0;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << real_;
        if (imag_ >= 0) oss << "+";
        oss << imag_ << "j";
        return oss.str();
    }

private:
    double real_;
    double imag_;
};

class ComplexCalculator {
public:
    ComplexNumber add(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() + c2.getReal();
        double imag = c1.getImaginary() + c2.getImaginary();
        return ComplexNumber(real, imag);
    }

    ComplexNumber subtract(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() - c2.getReal();
        double imag = c1.getImaginary() - c2.getImaginary();
        return ComplexNumber(real, imag);
    }

    ComplexNumber multiply(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() * c2.getReal() - c1.getImaginary() * c2.getImaginary();
        double imag = c1.getReal() * c2.getImaginary() + c1.getImaginary() * c2.getReal();
        return ComplexNumber(real, imag);
    }

    ComplexNumber divide(const ComplexNumber& c1, const ComplexNumber& c2) {
        double denom = c2.getReal() * c2.getReal() + c2.getImaginary() * c2.getImaginary();
        double real = (c1.getReal() * c2.getReal() + c1.getImaginary() * c2.getImaginary()) / denom;
        double imag = (c1.getImaginary() * c2.getReal() - c1.getReal() * c2.getImaginary()) / denom;
        return ComplexNumber(real, imag);
    }
};