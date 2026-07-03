class CombinationCalculator:
    def __init__(self, datas):
        self.datas = datas

    @staticmethod
    def count(n, m):
        if m == 0 or n == m:
            return 1
        # integer division to match Java's int / int truncation
        return CombinationCalculator.factorial(n) // (CombinationCalculator.factorial(n - m) * CombinationCalculator.factorial(m))

    @staticmethod
    def factorial(x):
        result = 1
        for i in range(1, x + 1):
            result *= i
        return result

    @staticmethod
    def countAll(n):
        if n < 0 or n > 63:
            return float('nan')
        if n == 63:
            return float('inf')
        # simulate Java int left shift on 32-bit signed integer
        shift = n & 0x1f
        # compute (1 << shift) as a 32-bit signed int
        value = 1 << shift
        # mask to 32-bit unsigned, then convert to signed
        unsigned = value & 0xffffffff
        # convert to signed 32-bit via two's complement
        if unsigned >= 0x80000000:
            signed = unsigned - 0x100000000
        else:
            signed = unsigned
        # result = signed - 1, with 32-bit overflow handling
        result_unsigned = (signed - 1) & 0xffffffff
        if result_unsigned >= 0x80000000:
            result_int = result_unsigned - 0x100000000
        else:
            result_int = result_unsigned
        return float(result_int)

    def select(self, m):
        result = []
        self._select(0, [None] * m, 0, result, m)
        return result

    def selectAll(self):
        result = []
        for i in range(1, len(self.datas) + 1):
            result.extend(self.select(i))
        return result

    def _select(self, dataIndex, resultList, resultIndex, result, m):
        if resultIndex == m:
            result.append(resultList[:])
            return
        # number of elements available for current pick
        n_remaining = len(self.datas) - (m - resultIndex)
        for i in range(dataIndex, n_remaining + 1):
            resultList[resultIndex] = self.datas[i]
            self._select(i + 1, resultList, resultIndex + 1, result, m)
            # no need to clear the slot; it will be overwritten