class DataStatistics:
    def mean(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        total = sum(data)
        return round(total / len(data) * 100) / 100

    def median(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        data_sorted = sorted(data)
        n = len(data_sorted)
        if n % 2 == 0:
            middle_sum = (data_sorted[n//2 - 1] + data_sorted[n//2]) / 2
            return round(middle_sum * 100) / 100
        else:
            return data_sorted[n//2]

    def mode(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        count_map = {}
        for num in data:
            count_map[num] = count_map.get(num, 0) + 1
        max_count = max(count_map.values())
        modes = [num for num, count in count_map.items() if count == max_count]
        return modes