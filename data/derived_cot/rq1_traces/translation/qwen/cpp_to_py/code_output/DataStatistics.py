class DataStatistics:
    def mean(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        total = sum(data)
        return round(total / len(data), 2)
    
    def median(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            return round((sorted_data[n//2 - 1] + sorted_data[n//2]) / 2, 2)
        else:
            return sorted_data[n//2]
    
    def mode(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        from collections import Counter
        count_map = Counter(data)
        max_count = max(count_map.values())
        return [num for num, count in count_map.items() if count == max_count]