import math
from decimal import Decimal, getcontext, ROUND_HALF_UP

class TriCalculator:

    def __init__(self):
        pass

    def cos(self, x):
        return self.round(self._taylor(x, 50), 10)

    def sin(self, x):
        x_rad = x * math.pi / 180.0
        g = 0.0
        t = x_rad
        n = 1

        while abs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x_rad * x_rad / ((2*n-1) * (2*n-2))
        return self.round(g, 10)

    def tan(self, x):
        cos_value = self.cos(x)
        if cos_value != 0:
            return self.round(self.sin(x) / cos_value, 10)
        else:
            return float('nan')

    def _taylor(self, x, n):
        old_p = getcontext().prec
        getcontext().prec = 34

        x_rad = x * math.pi / 180.0
        count = 1
        a = Decimal('1')
        for k in range(1, n):
            term = (Decimal(str(x_rad)) ** (2*k)) / self._factorial(2*k)
            if count % 2 != 0:
                a -= term
            else:
                a += term
            count += 1

        getcontext().prec = old_p
        return float(a)

    def _factorial(self, a):
        result = Decimal('1')
        while a > 1:
            result = result * Decimal(str(a))
            a -= 1
        return result

    def round(self, value, places):
        decimal_value = Decimal(str(value))
        quantizer = Decimal('1e-{}'.format(places))
        rounded_value = decimal_value.quantize(quantizer, rounding=ROUND_HALF_UP)
        return float(rounded_value)