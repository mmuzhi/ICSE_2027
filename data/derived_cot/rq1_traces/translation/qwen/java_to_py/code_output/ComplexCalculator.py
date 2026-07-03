class ComplexCalculator:

    class ComplexNumber:
        def __init__(self, real, imaginary):
            self.real = real
            self.imaginary = imaginary

        def getReal(self):
            return self.real

        def getImaginary(self):
            return self.imaginary

        def __eq__(self, other):
            if isinstance(other, ComplexCalculator.ComplexNumber):
                return self.real == other.real and self.imaginary == other.imaginary
            return False

        def __str__(self):
            if self.imaginary == 0:
                return f"{self.real}+0j"
            elif self.real == 0:
                if self.imaginary >= 0:
                    return f"{self.imaginary}j"
                else:
                    return f"-{abs(self.imaginary)}j"
            else:
                if self.imaginary >= 0:
                    return f"{self.real}+{self.imaginary}j"
                else:
                    return f"{self.real}{self.imaginary}j"

    @staticmethod
    def add(c1, c2):
        real = c1.getReal() + c2.getReal()
        imaginary = c1.getImaginary() + c2.getImaginary()
        return ComplexCalculator.ComplexNumber(real, imaginary)

    @staticmethod
    def subtract(c1, c2):
        real = c1.getReal() - c2.getReal()
        imaginary = c1.getImaginary() - c2.getImaginary()
        return ComplexCalculator.ComplexNumber(real, imaginary)

    @staticmethod
    def multiply(c1, c2):
        real = c1.getReal() * c2.getReal() - c1.getImaginary() * c2.getImaginary()
        imaginary = c1.getReal() * c2.getImaginary() + c1.getImaginary() * c2.getReal()
        return ComplexCalculator.ComplexNumber(real, imaginary)

    @staticmethod
    def divide(c1, c2):
        denominator = c2.getReal() * c2.getReal() + c2.getImaginary() * c2.getImaginary()
        real = (c1.getReal() * c2.getReal() + c1.getImaginary() * c2.getImaginary()) / denominator
        imaginary = (c1.getImaginary() * c2.getReal() - c1.getReal() * c2.getImaginary()) / denominator
        return ComplexCalculator.ComplexNumber(real, imaginary)