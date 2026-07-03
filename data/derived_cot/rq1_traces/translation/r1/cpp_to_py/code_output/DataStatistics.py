class DataStatistics:
    def mean(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        total = sum(data)
        n = len(data)
        result = total / n
        return round(result * 100) / 100

    def median(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            mid1 = sorted_data[n // 2 - 1]
            mid2 = sorted_data[n // 2]
            result = (mid1 + mid2) / 2
            return round(result * 100) / 100
        else:
            return sorted_data[n // 2]

    def mode(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        count_map = {}
        for num in data:
            count_map[num] = count_map.get(num, 0) + 1
        
        max_count = max(count_map.values()) if count_map else 0
        
        modes = []
        for num in sorted(count_map.keys()):
            if count_map[num] == max_count:
                modes.append(num)
        return modes