from typing import List

class CombinationCalculator:
    def __init__(self, datas: List[str]):
        self.datas = datas

    @staticmethod
    def count(n: int, m: int) -> int:
        if m == 0 or n == m:
            return 1
        return CombinationCalculator._factorial(n) // (CombinationCalculator._factorial(n - m) * CombinationCalculator._factorial(m))

    @staticmethod
    def _factorial(x: int) -> int:
        result = 1
        for i in range(1, x + 1):
            result *= i
        return result

    @staticmethod
    def countAll(n: int) -> float:
        if n < 0 or n > 63:
            return float('nan')
        if n == 63:
            return float('inf')
        return float((1 << n) - 1)

    def select(self, m: int) -> List[List[str]]:
        result: List[List[str]] = []
        self._select(0, [], 0, result, m)
        return result

    def selectAll(self) -> List[List[str]]:
        result: List[List[str]] = []
        for i in range(1, len(self.datas) + 1):
            result.extend(self.select(i))
        return result

    def _select(self, data_index: int, result_list: List[str], result_index: int, result: List[List[str]], m: int) -> None:
        if result_index == m:
            result.append(result_list.copy())
            return

        for i in range(data_index, len(self.datas) - (m - result_index) + 1):
            result_list.insert(result_index, self.datas[i])
            self._select(i + 1, result_list, result_index + 1, result, m)
            del result_list[result_index]