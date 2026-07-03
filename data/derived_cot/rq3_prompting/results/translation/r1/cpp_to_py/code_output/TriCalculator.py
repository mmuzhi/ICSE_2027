import math

class TriCalculator:
    PI = 3.14159265358979323846

    def __init__(self):
        pass

    def _round(self, value: float, precision: int) -> float:
        """Round half away from zero (like C++ std::round)."""
        factor = 10.0 ** precision
        scaled = value * factor
        # compute floor(|scaled| + 0.5) with sign
        if scaled >= 0:
            rounded = math.floor(scaled + 0.5)
        else:
            rounded = -math.floor(-scaled + 0.5)
        return rounded / factor

    def factorial(self, a: int) -> int:
        if a < 0:
            return 0
        if a == 0:
            return 1
        b = 1
        for i in range(1, a + 1):
            b *= i
        return b

    def taylor(self, x: float, n: int) -> float:
        a = 0.0
        x = x / 180.0 * self.PI
        for k in range(n):
            term = math.pow(x, 2 * k) / self.factorial(2 * k)
            if k % 2 == 0:
                a += term
            else:
                a -= term
        return a

    def cos(self, x: float) -> float:
        result = self.taylor(x, 17)
        print("Taylor result for cos: " + str(result))
        return self._round(result, 10)

    def sin(self, x: float) -> float:
        x = x / 180.0 * self.PI
        g = 0.0
        t = x
        n = 1
        while abs(t) >= 1e-15:
            g += t
            n += 1
            t = -t * x * x / ((2 * n - 1) * (2 * n - 2))
        return self._round(g, 10)

    def tan(self, x: float) -> float:
        cosine = self.cos(x)
        if abs(cosine) > 0.01:
            result = self.sin(x) / cosine
            return self._round(result, 10)
        else:
            return float('nan')