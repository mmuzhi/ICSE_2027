import math
from collections import Counter
from typing import List


class DataStatistics:

    @staticmethod
    def _round_to_two(x: float) -> float:
        """Emulate Java's Math.round(x * 100) / 100.0 (round half up)."""
        return math.floor(x * 100 + 0.5) / 100.0

    def mean(self, data: List[int]) -> float:
        total = sum(data)
        return self._round_to_two(total / len(data))

    def median(self, data: List[int]) -> float:
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            mid = n // 2
            avg = (sorted_data[mid - 1] + sorted_data[mid]) / 2.0
            return self._round_to_two(avg)
        else:
            mid = n // 2
            return float(sorted_data[mid])

    def mode(self, data: List[int]) -> List[int]:
        freq = Counter(data)
        max_count = max(freq.values())
        modes = sorted(k for k, v in freq.items() if v == max_count)
        return modes