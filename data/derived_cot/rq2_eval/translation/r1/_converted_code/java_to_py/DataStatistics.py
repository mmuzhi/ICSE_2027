import math

class NoSuchElementException(Exception):
    pass

class DataStatistics:

    def mean(self, data):
        n = len(data)
        if n == 0:
            return 0.0
        total = sum(data)
        value = total / n
        scaled = value * 100.0
        rounded_scaled = math.floor(scaled + 0.5)
        return rounded_scaled / 100.0

    def median(self, data):
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            mid1 = sorted_data[n//2 - 1]
            mid2 = sorted_data[n//2]
            med = (mid1 + mid2) / 2.0
            scaled = med * 100.0
            rounded_scaled = math.floor(scaled + 0.5)
            return rounded_scaled / 100.0
        else:
            return float(sorted_data[n//2])

    def mode(self, data):
        if len(data) == 0:
            raise NoSuchElementException("No elements in data")
        
        freq = {}
        for num in data:
            freq[num] = freq.get(num, 0) + 1
        
        max_count = max(freq.values())
        modes = [key for key, count in freq.items() if count == max_count]
        modes.sort()
        return modes