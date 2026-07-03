import math
from decimal import Decimal, getcontext, ROUND_HALF_EVEN, ROUND_HALF_UP

# Set decimal context to match Java's MathContext.DECIMAL128 (34 digits, HALF_EVEN)
DECIMAL128_CONTEXT = getcontext().copy()
DECIMAL128_CONTEXT.prec = 34
DECIMAL128_CONTEXT.rounding = ROUND_HALF_EVEN

class TriCalculator:
    def __init__(self):
        pass

    def cos(self, x: float) -> float:
        return self.round(self.taylor(x, 50), 10)

    def factorial(self, a: int) -> Decimal:
        result = 1
        while a > 1:
            result *= a
            a -= 1
        return Decimal(result)

    def taylor(self, x: float, n: int) -> float:
        x = x / 180.0 * math.pi
        a = Decimal(1)
        count = 1
        for k in range(1, n):
            # Compute x^(2k) as double
            x_pow = math.pow(x, 2 * k)
            # Convert to Decimal and divide with DECIMAL128 precision
            term = Decimal(x_pow) / self.factorial(2 * k)  # uses current context? We'll use localcontext.
            # Actually need to use division with DECIMAL128_CONTEXT. We can do inside localcontext.
            # Use localcontext to ensure correct precision and rounding.
            with localcontext(DECIMAL128_CONTEXT):
                term = Decimal(x_pow) / self.factorial(2 * k)
            if count % 2 != 0:
                a = a - term
            else:
                a = a + term
            count += 1
        return float(a)

    def sin(self, x: float) -> float:
        x = x / 180.0 * math.pi
        g = 0.0
        t = x
        n = 1
        while abs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x * x / (2 * n - 1) / (2 * n - 2)
        return self.round(g, 10)

    def tan(self, x: float) -> float:
        cos_val = self.cos(x)
        if cos_val != 0.0:
            return self.round(self.sin(x) / cos_val, 10)
        else:
            return float('nan')

    def round(self, value: float, places: int) -> float:
        # Use string conversion to match Java's BigDecimal.valueOf(double)
        bd = Decimal(str(value))
        quantizer = Decimal('1.' + '0' * places)
        bd = bd.quantize(quantizer, rounding=ROUND_HALF_UP)
        return float(bd)