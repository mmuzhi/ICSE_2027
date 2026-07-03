class ComplexCalculator:
    @staticmethod
    def add(c1, c2):
        return complex(c1.real + c2.real, c1.imag + c2.imag)

    @staticmethod
    def subtract(c1, c2):
        return complex(c1.real - c2.real, c1.imag - c2.imag)

    @staticmethod
    def multiply(c1, c2):
        return complex(c1.real * c2.real - c1.imag * c2.imag, c1.real * c2.imag + c1.imag * c2.real)

    @staticmethod
    def divide(c1, c2):
        denominator = c2.real * c2.real + c2.imag * c2.imag
        real = (c1.real * c2.real + c1.imag * c2.imag) / denominator
        imaginary = (c1.imag * c2.real - c1.real * c2.imag) / denominator
        return complex(real, imaginary)