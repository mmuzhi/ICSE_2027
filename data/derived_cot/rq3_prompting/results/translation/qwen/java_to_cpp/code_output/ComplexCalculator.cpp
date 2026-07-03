#include <string>
#include <limits>

class ComplexNumber {
private:
    double real;
    double imaginary;

public:
    ComplexNumber(double real, double imaginary) : real(real), imaginary(imaginary) {}

    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    bool equals(const ComplexNumber& other) const {
        return (real == other.real) && (imaginary == other.imaginary);
    }

    std::string toString() const {
        std::string sign = (imaginary >= 0) ? "+" : "";
        return std::to_string(real) + sign + std::to_string(imaginary) + "j";
    }
};

class ComplexCalculator {
public:
    static ComplexNumber add(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() + c2.getReal();
        double imaginary = c1.getImaginary() + c2.getImaginary();
        return ComplexNumber(real, imaginary);
    }

    static ComplexNumber subtract(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() - c2.getReal();
        double imaginary = c1.getImaginary() - c2.getImaginary();
        return ComplexNumber(real, imaginary);
    }

    static ComplexNumber multiply(const ComplexNumber& c1, const ComplexNumber& c2) {
        double real = c1.getReal() * c2.getReal() - c1.getImaginary() * c2.getImaginary();
        double imaginary = c1.getReal() * c2.getImaginary() + c1.getImaginary() * c2.getReal();
        return ComplexNumber(real, imaginary);
    }

    static ComplexNumber divide(const ComplexNumber& c1, const ComplexNumber& c2) {
        double denominator = c2.getReal() * c2.getReal() + c2.getImaginary() * c2.getImaginary();
        if (denominator == 0) {
            return ComplexNumber(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
        }
        double real = (c1.getReal() * c2.getReal() + c1.getImaginary() * c2.getImaginary()) / denominator;
        double imaginary = (c1.getImaginary() * c2.getReal() - c1.getReal() * c2.getImaginary()) / denominator;
        return ComplexNumber(real, imaginary);
    }
};