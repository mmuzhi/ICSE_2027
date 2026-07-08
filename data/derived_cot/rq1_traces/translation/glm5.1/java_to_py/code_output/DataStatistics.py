import math
from collections import Counter
from typing import List


class DataStatistics:

    def mean(self, data: List[int]) -> float:
        if not data:
            return float('nan')
        
        sum_val = sum(data)
        val = sum_val / len(data)
        # Replicates Java's Math.round(val * 100.0) / 100.0 
        # (round half up, away from zero)
        return math.floor(val * 100.0 + 0.5) / 100.0

    def median(self, data: List[int]) -> float:
        sorted_data = sorted(data)
        n = len(sorted_data)

        if n % 2 == 0:
            middle = n // 2
            val = (sorted_data[middle - 1] + sorted_data[middle]) / 2.0
            return math.floor(val * 100.0 + 0.5) / 100.0
        else:
            middle = n // 2
            return float(sorted_data[middle])

    def mode(self, data: List[int]) -> List[int]:
        counts = Counter(data)
        max_count = max(counts.values())
        
        modes = [k for k, v in counts.items() if v == max_count]
        modes.sort()
        return modes