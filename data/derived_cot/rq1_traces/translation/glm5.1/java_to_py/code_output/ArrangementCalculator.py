from typing import List, Optional, Any

class ArrangementCalculator:
    def __init__(self, datas: List[Any]):
        self.datas = datas

    @staticmethod
    def count(n: int, m: Optional[int]) -> int:
        if m is None or n == m:
            return ArrangementCalculator.factorial(n)
        else:
            # Use // for integer division to match Java's int division behavior
            return ArrangementCalculator.factorial(n) // ArrangementCalculator.factorial(n - m)

    @staticmethod
    def countAll(n: int) -> int:
        total = 0
        for i in range(1, n + 1):
            total += ArrangementCalculator.count(n, i)
        return total

    def select(self, m: Optional[int] = None) -> List[List[Any]]:
        if m is None:
            m = len(self.datas)
        result: List[List[Any]] = []
        self._selectPermutations([], list(self.datas), m, result)
        return result

    def selectAll(self) -> List[List[Any]]:
        result: List[List[Any]] = []
        for i in range(1, len(self.datas) + 1):
            result.extend(self.select(i))
        return result

    def _selectPermutations(self, prefix: List[Any], remaining: List[Any], m: int, result: List[List[Any]]) -> None:
        if len(prefix) == m:
            result.append(list(prefix))
            return
        for i in range(len(remaining)):
            new_prefix = list(prefix)
            new_prefix.append(remaining[i])
            new_remaining = list(remaining)
            # Equivalent to Java's List.remove(int index), removing by index, not by value
            del new_remaining[i]
            self._selectPermutations(new_prefix, new_remaining, m, result)

    @staticmethod
    def factorial(n: int) -> int:
        result = 1
        for i in range(2, n + 1):
            result *= i
        return result