import math
import sys

class CombinationCalculator:
    def __init__(self, datas):
        self.datas = datas

    @staticmethod
    def count(n, m):
        if m == 0 or n == m:
            return 1
        return int(round(math.gamma(n + 1) / (math.gamma(m + 1) * math.gamma(n - m + 1))))

    @staticmethod
    def count_all(n):
        if n < 0:
            return math.nan
        if n >= 63:
            return math.inf
        return (1 << n) - 1

    def select(self, m):
        n = len(self.datas)
        if m < 0 or m > n:
            return []
        result = []
        result_list = [''] * m
        self._select(0, result_list, 0, result)
        return result

    def select_all(self):
        result = []
        n = len(self.datas)
        for i in range(1, n + 1):
            combs = self.select(i)
            result.extend(combs)
        return result

    def _select(self, data_index, result_list, result_index, result):
        if result_index == len(result_list):
            result.append(result_list[:])
            return
        n = len(self.datas)
        available = n - data_index
        needed = len(result_list) - result_index
        if available < needed:
            return
        end_index = n - needed + 1
        for i in range(data_index, end_index):
            result_list[result_index] = self.datas[i]
            self._select(i + 1, result_list, result_index + 1, result)