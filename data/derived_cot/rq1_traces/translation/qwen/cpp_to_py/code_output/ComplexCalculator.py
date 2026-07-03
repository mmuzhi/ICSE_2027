class ComplexCalculator:
    @staticmethod
    def add(c1, c2):
        return c1 + c2

    @staticmethod
    def subtract(c1, c2):
        return c1 - c2

    @staticmethod
    def multiply(c1, c2):
        return c1 * c2

    @staticmethod
    def divide(c1, c2):
        denominator = c2.real ** 2 + c2.imag ** 2
        if denominator == 0:
            return complex(float('nan'), float('nan'))
        real = (c1.real * c2.real + c1.imag * c2.imag) / denominator
        imaginary = (c1.imag * c2.real - c1.real * c2.imag) / denominator
        return complex(real, imaginary)