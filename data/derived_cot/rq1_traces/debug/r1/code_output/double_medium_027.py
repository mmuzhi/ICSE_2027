from math import ceil
from typing import List

class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        n = len(dist)
        if hour <= n - 1:
            return -1
        
        left, right = 1, 10**7
        while left < right:
            mid = (left + right) // 2
            total_time = sum(ceil(d / mid) for d in dist[:-1]) + dist[-1] / mid
            if total_time <= hour:
                right = mid
            else:
                left = mid + 1
        return left