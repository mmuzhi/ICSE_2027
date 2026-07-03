import math
from collections import Counter


class DataStatistics:

    def mean(self, data):
        s = sum(data)
        return math.floor(s / len(data) * 100 + 0.5) / 100

    def median(self, data):
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            middle = n // 2
            return math.floor((sorted_data[middle - 1] + sorted_data[middle]) / 2.0 * 100 + 0.5) / 100
        else:
            middle = n // 2
            return sorted_data[middle]

    def mode(self, data):
        counter = Counter(data)
        max_count = max(counter.values())
        return sorted([k for k, v in counter.items() if v == max_count])