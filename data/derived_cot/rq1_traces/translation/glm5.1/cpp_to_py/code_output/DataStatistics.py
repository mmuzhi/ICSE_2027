import math

class DataStatistics:
    @staticmethod
    def _round_half_away_from_zero(x):
        """Mimics C++ std::round behavior (rounds half away from zero)."""
        if x >= 0:
            return math.floor(x + 0.5)
        else:
            return math.ceil(x - 0.5)

    def mean(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        
        sum_val = sum(data)
        return DataStatistics._round_half_away_from_zero(sum_val / len(data) * 100) / 100

    def median(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        
        # C++ passes by value, so we must not modify the original list.
        sorted_data = sorted(data)
        n = len(sorted_data)
        
        if n % 2 == 0:
            return DataStatistics._round_half_away_from_zero(((sorted_data[n // 2 - 1] + sorted_data[n // 2]) / 2) * 100) / 100
        else:
            return sorted_data[n // 2]

    def mode(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        
        count_map = {}
        for num in data:
            count_map[num] = count_map.get(num, 0) + 1
        
        max_count = 0
        # std::map iterates in sorted key order
        for key in sorted(count_map.keys()):
            if count_map[key] > max_count:
                max_count = count_map[key]
        
        modes = []
        # std::map iterates in sorted key order
        for key in sorted(count_map.keys()):
            if count_map[key] == max_count:
                modes.append(key)
                
        return modes