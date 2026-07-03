import math

class TriCalculator:
    PI = math.pi

    def __init__(self):
        pass

    def round(self, value, precision):
        factor = 10.0 ** precision
        return round(value * factor) / factor

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
        x_rad = x * (math.pi / 180)
        for k in range(n):
            term = (x_rad ** (2 * k)) / self.factorial(2 * k)
            if k % 2 == 0:
                a += term
            else:
                a -= term
        return a

    def cos(self, x):
        x_rad = x * (math.pi / 180)
        result = self.taylor(x_rad, 17)
        print("Taylor result for cos:", result)
        return self.round(result, 10)

    def sin(self, x):
        x_rad = x * (math.pi / 180)
        g = 0.0
        t = x_rad
        n = 1
        while abs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x_rad * x_rad / ((2 * n - 1) * (2 * n - 2))
        return self.round(g, 10)

    def tan(self, x):
        cosine = self.cos(x)
        if abs(cosine) > 0.01:
            result = self.sin(x) / cosine
            return self.round(result, 10)
        else:
            return float('nan')