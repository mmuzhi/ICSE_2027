import math
from decimal import Decimal, localcontext, ROUND_HALF_UP


class TriCalculator:

    def __init__(self):
        pass

    def cos(self, x):
        return self.round(self.taylor(x, 50), 10)

    def factorial(self, a):
        result = Decimal(1)
        while a > 1:
            result = result * Decimal(a)
            a -= 1
        return result

    def taylor(self, x, n):
        a = Decimal(1)
        x = x / 180 * math.pi
        count = 1
        for k in range(1, n):
            fact = self.factorial(2 * k)
            with localcontext() as ctx:
                ctx.prec = 38  # DECIMAL128 precision
                term = Decimal(str(math.pow(x, 2 * k))) / fact
            if count % 2 != 0:
                a = a - term
            else:
                a = a + term
            count += 1
        return float(a)

    def sin(self, x):
        x = x / 180 * math.pi
        g = 0.0
        t = x
        n = 1
        while abs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x * x / (2 * n - 1) / (2 * n - 2)
        return self.round(g, 10)

    def tan(self, x):
        cos_value = self.cos(x)
        if cos_value != 0:
            return self.round(self.sin(x) / cos_value, 10)
        else:
            return float('nan')

    def round(self, value, places):
        bd = Decimal(str(value))
        bd = bd.quantize(Decimal(10) ** -places, rounding=ROUND_HALF_UP)
        return float(bd)