import math
from decimal import Decimal, ROUND_HALF_UP, getcontext

class TriCalculator:
    def __init__(self):
        getcontext().prec = 128

    def factorial(self, a: int) -> Decimal:
        result = Decimal(1)
        for i in range(2, a + 1):
            result *= Decimal(i)
        return result

    def taylor(self, x: float, n: int) -> float:
        x_rad = x * math.pi / 180.0
        x_dec = Decimal(x_rad)
        a = Decimal(1)
        count = 1
        for k in range(1, n):
            term = x_dec ** (2 * k)
            term /= self.factorial(2 * k)
            if count % 2 == 1:
                a -= term
            else:
                a += term
            count += 1
        return float(a)

    def sin(self, x: float) -> float:
        x_rad = x * math.pi / 180.0
        g = 0.0
        t = x_rad
        n = 1
        while abs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x_rad * x_rad / (2 * n - 1) / (2 * n - 2)
        return self.round(g, 10)

    def cos(self, x: float) -> float:
        return self.round(self.taylor(x, 50), 10)

    def tan(self, x: float) -> float:
        cosValue = self.cos(x)
        if cosValue == 0:
            return float('nan')
        return self.round(self.sin(x) / cosValue, 10)

    def round(self, value: float, places: int) -> float:
        d = Decimal(value)
        if places >= 0:
            quantizer = Decimal('1.' + '0' * places)
        else:
            quantizer = Decimal('1' + '0' * (-places))
        d = d.quantize(quantizer, rounding=ROUND_HALF_UP)
        return float(d)