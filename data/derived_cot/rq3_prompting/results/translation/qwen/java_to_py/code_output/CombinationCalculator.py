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
    def countAll(n):
        if n < 0 or n > 63:
            return float('nan')
        return (1 << n) - 1 if n != 63 else float('inf')

    def select(self, m):
        result_list = []
        self._select(0, [], 0, result_list, m)
        return result_list

    def selectAll(self):
        result_list = []
        n = len(self.datas)
        for i in range(1, n + 1):
            result_list.extend(self.select(i))
        return result_list

    def _select(self, dataIndex, resultList, resultIndex, resultListContainer, m):
        if resultIndex == m:
            resultListContainer.append(resultList[:])
            return
        upper_bound = len(self.datas) - (m - resultIndex)
        for i in range(dataIndex, upper_bound + 1):
            resultList.insert(resultIndex, self.datas[i])
            self._select(i + 1, resultList, resultIndex + 1, resultListContainer, m)
            del resultList[resultIndex]