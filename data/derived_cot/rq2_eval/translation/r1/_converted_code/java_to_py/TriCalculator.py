import math
import decimal

class TriCalculator:
    def __init__(self):
        pass

    def cos(self, x):
        return self.round(self.taylor(x, 50), 10)

    def factorial(self, a):
        result = decimal.Decimal(1)
        while a > 1:
            result = result * decimal.Decimal(a)
            a -= 1
        return result

    def taylor(self, x, n):
        x_rad = x * math.pi / 180.0
        a = decimal.Decimal(1)
        count = 1
        with decimal.localcontext() as ctx:
            ctx.prec = 34
            for k in range(1, n):
                power_val = math.pow(x_rad, 2 * k)
                term = decimal.Decimal(str(power_val))
                term = term / self.factorial(2 * k)
                if count % 2 != 0:
                    a -= term
                else:
                    a += term
                count += 1
        return float(a)

    def sin(self, x):
        x_rad = x * math.pi / 180.0
        g = 0.0
        t = x_rad
        n = 1
        while abs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x_rad * x_rad / ((2 * n - 1) * (2 * n - 2))
        return self.round(g, 10)

    def tan(self, x):
        cos_value = self.cos(x)
        if cos_value != 0.0:
            sin_value = self.sin(x)
            return self.round(sin_value / cos_value, 10)
        else:
            return float('nan')

    def round(self, value, places):
        if math.isnan(value) or math.isinf(value):
            raise ValueError("Cannot convert NaN or infinity to Decimal")
        d = decimal.Decimal(str(value))
        scale = decimal.Decimal(10) ** -places
        rounded_d = d.quantize(scale, rounding=decimal.ROUND_HALF_UP)
        return float(rounded_d)