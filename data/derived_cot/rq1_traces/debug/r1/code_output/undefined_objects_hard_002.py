from typing import List

class Solution:
    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        start, end = min(stations), sum(stations) + k
        while start < end:
            mid = (start + end + 1) // 2
            if self.check(stations, r, k, mid):
                start = mid
            else:
                end = mid - 1
        return start
    
    def check(self, stations: List[int], r: int, k: int, target: int) -> bool:
        n = len(stations)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + stations[i]
        added = [0] * (n + 1)
        current_add = 0
        for i in range(n):
            current_add += added[i]
            start_window = max(0, i - r)
            end_window = min(n - 1, i + r)
            total_power = (prefix[end_window + 1] - prefix[start_window]) + current_add
            if total_power < target:
                needed = target - total_power
                if needed > k:
                    return False
                k -= needed
                add_pos = end_window
                current_add += needed
                if add_pos + 1 < n:
                    added[add_pos + 1] -= needed
        return True