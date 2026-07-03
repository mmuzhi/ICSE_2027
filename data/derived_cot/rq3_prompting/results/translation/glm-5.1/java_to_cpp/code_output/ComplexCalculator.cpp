#include <cmath>
#include <string>

class ComplexNumber {
private:
    double real;
    double imaginary;

    static int doubleCompare(double a, double b) {
        if (std::isnan(a) && std::isnan(b)) return 0;
        if (std::isnan(a)) return 1;
        if (std::isnan(b)) return -1;
        if (a == 0.0 && b == 0.0) {
            int signA = std::signbit(a) ? -1 : 1;
            int signB = std::signbit(b) ? -1 : 1;
            return signA - signB;
        }
        if (a < b) return -1;
        if (a > b) return 1;
        return 0;
    }

public:
    ComplexNumber(double real, double imaginary) : real(real), imaginary(imaginary) {}

    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    bool equals(const ComplexNumber& that) const {
        return doubleCompare(real, that.real) == 0 && doubleCompare(imaginary, that.imaginary) == 0;
    }

    bool operator==(const ComplexNumber& that) const {
        return equals(that);
    }

    std::string toString() const {
        return std::to_string(real) + (imaginary >= 0 ? "+" : "") + std::to_string(imaginary) + "j";
    }
};

class ComplexCalculator {
public:
    ComplexNumber add(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() + c2.getReal();
        double imaginary = c1.getImaginary() + c2.getImaginary();
        return ComplexNumber(real, imaginary);
    }

    ComplexNumber subtract(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() - c2.getReal();
        double imaginary = c1.getImaginary() - c2.getImaginary();
        return ComplexNumber(real, imaginary);
    }

    ComplexNumber multiply(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() * c2.getReal() - c1.getImaginary() * c2.getImaginary();
        double imaginary = c1.getReal() * c2.getImaginary() + c1.getImaginary() * c2.getReal();
        return ComplexNumber(real, imaginary);
    }

    ComplexNumber divide(const ComplexNumber& c1, const ComplexNumber& c2) {
        double denominator = c2.getReal() * c2.getReal() + c2.getImaginary() * c2.getImaginary();
        double real = (c1.getReal() * c2.getReal() + c1.getImaginary() * c2.getImaginary()) / denominator;
        double imaginary = (c1.getImaginary() * c2.getReal() - c1.getReal() * c2.getImaginary()) / denominator;
        return ComplexNumber(real, imaginary);
    }
};