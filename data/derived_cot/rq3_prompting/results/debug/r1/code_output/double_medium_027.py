from typing import List
from math import ceil

class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        if hour <= len(dist) - 1:
            return -1
        left, right = 1, 10**7
        while left < right:
            mid = (left + right) // 2
            total = sum(ceil(d / mid) for d in dist[:-1]) + (dist[-1] / mid)
            if total <= hour:
                right = mid
            else:
                left = mid + 1
        return left