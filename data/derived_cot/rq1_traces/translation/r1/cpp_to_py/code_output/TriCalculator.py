import math

class TriCalculator:
    PI = math.pi

    def __init__(self):
        pass

    def round(self, value, precision):
        if math.isnan(value):
            return value
        factor = 10.0 ** precision
        scaled = value * factor
        if scaled >= 0:
            temp = math.floor(scaled + 0.5)
        else:
            temp = math.ceil(scaled - 0.5)
        return temp / factor

    def cos(self, x):
        result = self.taylor(x, 17)
        print(f"Taylor result for cos: {result}")
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
        x_rad = x / 180.0 * self.PI
        for k in range(n):
            exponent = 2 * k
            term = (x_rad ** exponent) / self.factorial(exponent)
            if k % 2 == 0:
                a += term
            else:
                a -= term
        return a

    def sin(self, x):
        x_rad = x / 180.0 * self.PI
        g = 0.0
        t = x_rad
        n = 1
        while math.fabs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x_rad * x_rad / ((2 * n - 1) * (2 * n - 2))
        return self.round(g, 10)

    def tan(self, x):
        cosine = self.cos(x)
        if math.fabs(cosine) > 0.01:
            sine_val = self.sin(x)
            result = sine_val / cosine
            return self.round(result, 10)
        else:
            return math.nan