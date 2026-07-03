import math
import sys

class CombinationCalculator:
    def __init__(self, datas):
        self.datas = list(datas)

    @staticmethod
    def count(n, m):
        if m == 0 or n == m:
            return 1
        return int(math.gamma(n + 1) / (math.gamma(m + 1) * math.gamma(n - m + 1)))

    @staticmethod
    def count_all(n):
        if n < 0:
            return float('nan')
        if n > 63:
            return float('inf')
        return (1 << n) - 1 if n != 63 else float('inf')

    def select(self, m):
        if m < 0 or m > len(self.datas):
            return []
        result = []
        self._select(0, [], 0, result, m)
        return result

    def select_all(self):
        result = []
        for i in range(1, len(self.datas) + 1):
            result.extend(self.select(i))
        return result

    def _select(self, dataIndex, resultList, resultIndex, result, m):
        if resultIndex == m:
            result.append(resultList[:])
            return
        
        max_index = len(self.datas) - (m - resultIndex)
        for i in range(dataIndex, max_index + 1):
            resultList.append(self.datas[i])
            self._select(i + 1, resultList, resultIndex + 1, result, m)
            resultList.pop()