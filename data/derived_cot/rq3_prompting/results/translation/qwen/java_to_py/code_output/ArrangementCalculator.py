import math
from typing import List, Optional

class ArrangementCalculator:
    def __init__(self, datas: List) -> None:
        self.datas = datas

    @staticmethod
    def count(n: int, m: Optional[int] = None) -> int:
        if m is None or n == m:
            return math.factorial(n)
        else:
            return math.factorial(n) // math.factorial(n - m)

    @staticmethod
    def count_all(n: int) -> int:
        total = 0
        for i in range(1, n + 1):
            total += ArrangementCalculator.count(n, i)
        return total

    def select(self, m: Optional[int] = None) -> List[List]:
        if m is None:
            m = len(self.datas)
        result = []
        self._select_permutations([], self.datas[:], m, result)
        return result

    def select_all(self) -> List[List]:
        result = []
        for i in range(1, len(self.datas) + 1):
            result.extend(self.select(i))
        return result

    def _select_permutations(self, prefix: List, remaining: List, m: int, result: List) -> None:
        if len(prefix) == m:
            result.append(prefix[:])
            return
        for i in range(len(remaining)):
            new_prefix = prefix + [remaining[i]]
            new_remaining = remaining[:i] + remaining[i+1:]
            self._select_permutations(new_prefix, new_remaining, m, result)

    @staticmethod
    def factorial(n: int) -> int:
        return math.factorial(n)