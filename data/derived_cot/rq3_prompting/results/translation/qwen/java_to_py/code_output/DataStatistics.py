import math
from collections import Counter

class DataStatistics:

    def mean(self, data):
        if not data:
            raise ZeroDivisionError("Cannot compute mean of empty array")
        return round(sum(data) / len(data), 2)

    def median(self, data):
        if not data:
            raise ZeroDivisionError("Cannot compute median of empty array")
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            middle = n // 2
            avg = (sorted_data[middle-1] + sorted_data[middle]) / 2.0
            return round(avg, 2)
        else:
            middle = n // 2
            return sorted_data[middle]

    def mode(self, data):
        if not data:
            raise ValueError("Empty array for mode")
        frequency_map = Counter(data)
        max_count = max(frequency_map.values())
        mode_values = [num for num, count in frequency_map.items() if count == max_count]
        mode_values.sort()
        return mode_values