import math

class CombinationCalculator:

    def __init__(self, datas):
        self.datas = datas

    @staticmethod
    def count(n, m):
        if m == 0 or n == m:
            return 1
        return CombinationCalculator.factorial(n) // (CombinationCalculator.factorial(n - m) * CombinationCalculator.factorial(m))

    @staticmethod
    def factorial(x):
        result = 1
        for i in range(1, x + 1):
            result *= i
        return result

    @staticmethod
    def count_all(n):
        if n < 0 or n > 63:
            return math.nan
        if n == 63:
            return math.inf
        n_mod = n % 32
        return float((1 << n_mod) - 1)

    def select(self, m):
        result = []
        self._select(0, [], 0, result, m)
        return result

    def select_all(self):
        result = []
        n = len(self.datas)
        for i in range(1, n + 1):
            result.extend(self.select(i))
        return result

    def _select(self, dataIndex, resultList, resultIndex, result, m):
        if resultIndex == m:
            result.append(resultList[:])
            return
        n = len(self.datas)
        for i in range(dataIndex, n - (m - resultIndex) + 1):
            resultList.insert(resultIndex, self.datas[i])
            self._select(i + 1, resultList, resultIndex + 1, result, m)
            resultList.pop(resultIndex)