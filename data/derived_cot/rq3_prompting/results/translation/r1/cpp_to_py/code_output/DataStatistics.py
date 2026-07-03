class DataStatistics:
    @staticmethod
    def _round_half_up(x: float) -> int:
        """Round to the nearest integer, ties away from zero (like C++ std::round)."""
        if x >= 0:
            return int(x + 0.5)
        else:
            return int(x - 0.5)

    def mean(self, data: list[float]) -> float:
        if not data:
            raise ValueError("Data vector is empty.")
        total = sum(data)
        # round to two decimal places
        return self._round_half_up(total / len(data) * 100) / 100.0

    def median(self, data: list[float]) -> float:
        if not data:
            raise ValueError("Data vector is empty.")
        sorted_data = sorted(data)
        n = len(sorted_data)
        if n % 2 == 0:
            # even: average of two middle values, rounded
            avg = (sorted_data[n // 2 - 1] + sorted_data[n // 2]) / 2.0
            return self._round_half_up(avg * 100) / 100.0
        else:
            # odd: middle value directly (no rounding)
            return sorted_data[n // 2]

    def mode(self, data: list[int]) -> list[int]:
        if not data:
            raise ValueError("Data vector is empty.")
        # count frequencies
        count_map = {}
        for num in data:
            count_map[num] = count_map.get(num, 0) + 1
        # find maximum frequency
        max_count = max(count_map.values())
        # collect all numbers with that frequency
        modes = [num for num, cnt in count_map.items() if cnt == max_count]
        # ensure sorted order (matches C++ map iteration)
        modes.sort()
        return modes