import math

def _double_eq(a, b):
    """Helper to mimic Java's Double.compare(a, b) == 0 behavior."""
    if math.isnan(a) and math.isnan(b):
        return True
    if a == 0.0 and b == 0.0:
        # Distinguish between 0.0 and -0.0
        return math.copysign(1.0, a) == math.copysign(1.0, b)
    return a == b

def _java_div(num, den):
    """Helper to mimic Java's double division behavior (no ZeroDivisionError)."""
    if den == 0.0:
        if math.isnan(num):
            return float('nan')
        if num == 0.0:
            return float('nan')
        return math.copysign(float('inf'), num)
    return num / den

def _java_str(f):
    """Helper to mimic Java's Double.toString() behavior for special values."""
    if math.isnan(f):
        return "NaN"
    if math.isinf(f):
        return "Infinity" if f > 0 else "-Infinity"
    return str(f)

class ComplexCalculator:

    class ComplexNumber:
        def __init__(self, real, imaginary):
            self.real = real
            self.imaginary = imaginary

        def getReal(self):
            return self.real

        def getImaginary(self):
            return self.imaginary

        def __eq__(self, obj):
            if self is obj:
                return True
            if obj is None or type(self) is not type(obj):
                return False
            return _double_eq(self.real, obj.real) and _double_eq(self.imaginary, obj.imaginary)

        def __hash__(self):
            # Mimic Java's default identity-based hashCode
            return id(self)

        def __str__(self):
            real_str = _java_str(self.real)
            imag_str = _java_str(self.imaginary)
            sign = "+" if self.imaginary >= 0 else ""
            return f"{real_str}{sign}{imag_str}j"

    def add(self, c1, c2):
        real = c1.getReal() + c2.getReal()
        imaginary = c1.getImaginary() + c2.getImaginary()
        return ComplexCalculator.ComplexNumber(real, imaginary)

    def subtract(self, c1, c2):
        real = c1.getReal() - c2.getReal()
        imaginary = c1.getImaginary() - c2.getImaginary()
        return ComplexCalculator.ComplexNumber(real, imaginary)

    def multiply(self, c1, c2):
        real = c1.getReal() * c2.getReal() - c1.getImaginary() * c2.getImaginary()
        imaginary = c1.getReal() * c2.getImaginary() + c1.getImaginary() * c2.getReal()
        return ComplexCalculator.ComplexNumber(real, imaginary)

    def divide(self, c1, c2):
        denominator = c2.getReal() * c2.getReal() + c2.getImaginary() * c2.getImaginary()
        real = _java_div(c1.getReal() * c2.getReal() + c1.getImaginary() * c2.getImaginary(), denominator)
        imaginary = _java_div(c1.getImaginary() * c2.getReal() - c1.getReal() * c2.getImaginary(), denominator)
        return ComplexCalculator.ComplexNumber(real, imaginary)