import math

class ComplexCalculator:
    class ComplexNumber:
        def __init__(self, real: float, imaginary: float):
            self._real = real
            self._imaginary = imaginary

        def get_real(self) -> float:
            return self._real

        def get_imaginary(self) -> float:
            return self._imaginary

        # Provide property access for convenience (not required but idiomatic)
        real = property(get_real)
        imaginary = property(get_imaginary)

        def __eq__(self, other):
            if not isinstance(other, ComplexCalculator.ComplexNumber):
                return False
            # Replicate Java's Double.compare behavior:
            # - NaN is equal to NaN (any sign).
            # - -0.0 != 0.0.
            # - All other values compared exactly.
            return _double_equals(self._real, other._real) and _double_equals(self._imaginary, other._imaginary)

        # Keep identity-based hashing (like Java's default hashCode)
        __hash__ = object.__hash__

        def __str__(self):
            # Mirror Java's toString: "real[+|-]imaginaryj"
            sign = "+" if self._imaginary >= 0 else ""
            return f"{self._real}{sign}{self._imaginary}j"

        def __repr__(self):
            return f"ComplexNumber({self._real}, {self._imaginary})"

    def add(self, c1, c2):
        real = c1.get_real() + c2.get_real()
        imag = c1.get_imaginary() + c2.get_imaginary()
        return ComplexCalculator.ComplexNumber(real, imag)

    def subtract(self, c1, c2):
        real = c1.get_real() - c2.get_real()
        imag = c1.get_imaginary() - c2.get_imaginary()
        return ComplexCalculator.ComplexNumber(real, imag)

    def multiply(self, c1, c2):
        a, b = c1.get_real(), c1.get_imaginary()
        c, d = c2.get_real(), c2.get_imaginary()
        real = a * c - b * d
        imag = a * d + b * c
        return ComplexCalculator.ComplexNumber(real, imag)

    def divide(self, c1, c2):
        a, b = c1.get_real(), c1.get_imaginary()
        c, d = c2.get_real(), c2.get_imaginary()
        denom = c * c + d * d
        real = (a * c + b * d) / denom
        imag = (b * c - a * d) / denom
        return ComplexCalculator.ComplexNumber(real, imag)


# Helper to mimic Java's Double.compare(a, b) == 0.
def _double_equals(a: float, b: float) -> bool:
    # Treat all NaN as equal
    if math.isnan(a) and math.isnan(b):
        return True
    if math.isnan(a) or math.isnan(b):
        return False
    # Exact equality plus sign check for zero
    if a == b:
        # For +0.0 and -0.0, a==b is True but we need to distinguish
        return math.copysign(1.0, a) == math.copysign(1.0, b)
    return False