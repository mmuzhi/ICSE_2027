import math

class DataStatistics:
    @staticmethod
    def _cpp_round(x):
        # C++ std::round rounds half away from zero, unlike Python's round which uses banker's rounding.
        if x >= 0:
            return math.floor(x + 0.5)
        else:
            return math.ceil(x - 0.5)

    def mean(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        total = sum(data)
        return self._cpp_round(total / len(data) * 100) / 100

    def median(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        data = sorted(data)
        n = len(data)
        if n % 2 == 0:
            return self._cpp_round(((data[n // 2 - 1] + data[n // 2]) / 2) * 100) / 100
        else:
            return data[n // 2]

    def mode(self, data):
        if not data:
            raise ValueError("Data vector is empty.")
        
        count_map = {}
        for num in data:
            count_map[num] = count_map.get(num, 0) + 1

        max_count = 0
        for count in count_map.values():
            if count > max_count:
                max_count = count

        modes = []
        # std::map iterates in sorted key order, so we sort the keys to match behavior
        for key in sorted(count_map.keys()):
            if count_map[key] == max_count:
                modes.append(key)

        return modes