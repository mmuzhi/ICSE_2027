import math

class CombinationCalculator:
    @staticmethod
    def count(n, m):
        if m == 0 or n == m:
            return 1
        try:
            numerator = math.gamma(n + 1)
            denominator = math.gamma(m + 1) * math.gamma(n - m + 1)
            value = numerator / denominator
            return int(value)
        except Exception:
            raise

    @staticmethod
    def count_all(n):
        if n < 0:
            return float('nan')
        if n >= 63:
            return float('inf')
        return (1 << n) - 1

    def __init__(self, datas):
        self.datas = datas

    def select(self, m):
        if m < 0 or m > len(self.datas):
            return []
        resultList = [''] * m
        result = []
        self._select(0, resultList, 0, result)
        return result

    def select_all(self):
        result = []
        for i in range(1, len(self.datas) + 1):
            result.extend(self.select(i))
        return result

    def _select(self, dataIndex, resultList, resultIndex, result):
        if resultIndex == len(resultList):
            result.append(resultList[:])
            return
        
        remaining = len(resultList) - resultIndex
        for i in range(dataIndex, len(self.datas) - remaining + 1):
            resultList[resultIndex] = self.datas[i]
            self._select(i + 1, resultList, resultIndex + 1, result)