import math


class TriCalculator:
    PI = 3.14159265358979323846

    def __init__(self):
        pass

    @staticmethod
    def _cpp_round(value):
        if value >= 0:
            return math.floor(value + 0.5)
        else:
            return math.ceil(value - 0.5)

    def round(self, value, precision):
        factor = math.pow(10.0, precision)
        return self._cpp_round(value * factor) / factor

    def cos(self, x):
        result = self.taylor(x, 17)
        print("Taylor result for cos: " + str(result))
        return self.round(result, 10)

    def factorial(self, a):
        if a < 0:
            return 0
        if a == 0:
            return 1
        b = 1
        for i in range(1, a + 1):
            b *= i
        return b

    def taylor(self, x, n):
        a = 0.0
        x = x / 180.0 * self.PI
        for k in range(n):
            term = math.pow(x, 2 * k) / self.factorial(2 * k)
            if k % 2 == 0:
                a += term
            else:
                a -= term
        return a

    def sin(self, x):
        x = x / 180.0 * self.PI
        g = 0.0
        t = x
        n = 1
        while math.fabs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x * x / ((2 * n - 1) * (2 * n - 2))
        return self.round(g, 10)

    def tan(self, x):
        cosine = self.cos(x)
        if math.fabs(cosine) > 0.01:
            result = self.sin(x) / cosine
            return self.round(result, 10)
        else:
            return math.nan