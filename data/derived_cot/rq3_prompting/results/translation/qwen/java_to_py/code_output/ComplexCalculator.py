import cmath
import math

class ComplexNumber:
    def __init__(self, real, imaginary):
        self.real = real
        self.imaginary = imaginary

    def __eq__(self, other):
        if not isinstance(other, ComplexNumber):
            return False
        # Check NaN for real part
        if (self.real != self.real) != (other.real != other.real):
            return False
        # Check NaN for imaginary part
        if (self.imaginary != self.imaginary) != (other.imaginary != other.imaginary):
            return False
        # If both real and imaginary parts are NaN, they are considered equal
        if (self.real != self.real) and (self.imaginary != self.imaginary):
            return True
        # Otherwise, use direct comparison
        return self.real == other.real and self.imaginary == other.imaginary

    def __str__(self):
        if self.imaginary >= 0:
            return f"{self.real}+{self.imaginary}j"
        else:
            return f"{self.real}{self.imaginary}j"

class ComplexCalculator:
    @staticmethod
    def add(c1, c2):
        real = c1.real + c2.real
        imaginary = c1.imaginary + c2.imaginary
        return ComplexNumber(real, imaginary)

    @staticmethod
    def subtract(c1, c2):
        real = c1.real - c2.real
        imaginary = c1.imaginary - c2.imaginary
        return ComplexNumber(real, imaginary)

    @staticmethod
    def multiply(c1, c2):
        real = c1.real * c2.real - c1.imaginary * c2.imaginary
        imaginary = c1.real * c2.imaginary + c1.imaginary * c2.real
        return ComplexNumber(real, imaginary)

    @staticmethod
    def divide(c1, c2):
        denominator = c2.real**2 + c2.imaginary**2
        if denominator == 0:
            raise ValueError("Division by zero")
        real = (c1.real * c2.real + c1.imaginary * c2.imaginary) / denominator
        imaginary = (c1.imaginary * c2.real - c1.real * c2.imaginary) / denominator
        return ComplexNumber(real, imaginary)