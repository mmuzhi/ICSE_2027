#include <cmath>
#include <sstream>
#include <stdexcept>
#include <string>

class ComplexCalculator {
public:
    class ComplexNumber {
    private:
        double real;
        double imaginary;

    public:
        ComplexNumber(double real, double imaginary) : real(real), imaginary(imaginary) {}

        double getReal() const { return real; }
        double getImaginary() const { return imaginary; }

        bool operator==(const ComplexNumber& other) const {
            // Handle NaN cases as in Java's Double.compare
            if (std::isnan(real) && std::isnan(other.real) && 
                std::isnan(imaginary) && std::isnan(other.imaginary)) {
                return true;
            }
            if (std::isnan(real) || std::isnan(other.real) ||
                std::isnan(imaginary) || std::isnan(other.imaginary)) {
                return false;
            }
            return (real == other.real) && (imaginary == other.imaginary);
        }

        std::string toString() const {
            std::ostringstream oss;
            oss << real;
            if (imaginary >= 0) {
                oss << "+";
            }
            oss << imaginary << "j";
            return oss.str();
        }
    };

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
            throw std::runtime_error("Division by zero");
        }
        double real = (c1.getReal() * c2.getReal() + c1.getImaginary() * c2.getImaginary()) / denominator;
        double imaginary = (c1.getImaginary() * c2.getReal() - c1.getReal() * c2.getImaginary()) / denominator;
        return ComplexNumber(real, imaginary);
    }
};