class DataStatistics:
    def mean(self, data):
        if len(data) == 0:
            raise ValueError("Mean cannot be calculated from an empty array.")
        total = sum(data)
        avg = total / len(data)
        return round(avg, 2)

    def median(self, data):
        if len(data) == 0:
            raise ValueError("Median cannot be calculated from an empty array.")
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            middle = n // 2
            avg = (sorted_data[middle - 1] + sorted_data[middle]) / 2.0
            return round(avg, 2)
        else:
            middle = n // 2
            return sorted_data[middle]

    def mode(self, data):
        if len(data) == 0:
            raise ValueError("Mode cannot be calculated from an empty array.")
        from collections import Counter
        freq_counter = Counter(data)
        max_freq = max(freq_counter.values())
        mode_values = [num for num, count in freq_counter.items() if count == max_freq]
        mode_values.sort()
        return mode_values