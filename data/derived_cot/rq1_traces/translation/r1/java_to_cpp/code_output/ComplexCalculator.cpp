#include <cmath>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <string>
#include <iostream>

class ComplexCalculator {
public:
    class ComplexNumber {
    private:
        double real;
        double imaginary;

    public:
        ComplexNumber(double real, double imaginary) : real(real), imaginary(imaginary) {}

        double getReal() const {
            return real;
        }

        double getImaginary() const {
            return imaginary;
        }

        bool equals(const ComplexNumber& that) const {
            return doubleCompare(real, that.real) == 0 && doubleCompare(imaginary, that.imaginary) == 0;
        }

        std::string toString() const {
            std::ostringstream oss;
            oss << real;
            if (imaginary >= 0) {
                oss << '+';
            }
            oss << imaginary << 'j';
            return oss.str();
        }

    private:
        static int doubleCompare(double a, double b) {
            if (std::isnan(a)) {
                if (std::isnan(b)) {
                    return 0;
                }
                return 1;
            }
            if (std::isnan(b)) {
                return -1;
            }
            if (a < b) {
                return -1;
            }
            if (a > b) {
                return 1;
            }

            uint64_t ua, ub;
            std::memcpy(&ua, &a, sizeof(double));
            std::memcpy(&ub, &b, sizeof(double));
            int64_t sa = static_cast<int64_t>(ua);
            int64_t sb = static_cast<int64_t>(ub);

            if (sa == sb) {
                return 0;
            }
            return sa < sb ? -1 : 1;
        }
    };

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

std::ostream& operator<<(std::ostream& os, const ComplexCalculator::ComplexNumber& cn) {
    os << cn.toString();
    return os;
}