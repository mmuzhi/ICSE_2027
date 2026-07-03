import math

class TriCalculator:
    PI = 3.14159265358979323846

    @staticmethod
    def round(value, precision):
        factor = 10.0 ** precision
        return round(value * factor) / factor

    def cos(self, x):
        result = self.taylor(x, 17)
        print(f"Taylor result for cos: {result}")
        return self.round(result, 10)

    @staticmethod
    def factorial(a):
        if a < 0:
            return 0
        if a == 0:
            return 1
        b = 1
        for i in range(1, a + 1):
            b *= i
        return b

    def taylor(self, x, n):
        x_rad = x * self.PI / 180.0
        result = 0.0
        term = x_rad
        for k in range(n):
            result += term
            term *= -x_rad * x_rad / ((2 * k + 1) * (2 * k + 2))
        return result

    def sin(self, x):
        x_rad = x * self.PI / 180.0
        result = 0.0
        term = x_rad
        while abs(term) >= 1e-15:
            result += term
            term *= -x_rad * x_rad / ((2 * (len(term.split()) + 1) - 2) * (2 * (len(term.split()) + 1) - 1))
        return self.round(result, 10)

    def tan(self, x):
        cosine = self.cos(x)
        if abs(cosine) > 0.01:
            return self.round(sin(x) / cosine, 10)
        else:
            return float('nan')