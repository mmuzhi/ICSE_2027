import math

class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        n = len(dist)
        if hour < n - 1:
            return -1
        
        left, right = 1, max(dist) * n
        
        while left < right:
            mid = (left + right) // 2
            total_time = sum(math.ceil(i / mid) for i in dist[:-1]) + (dist[-1] / mid)
            if total_time <= hour:
                right = mid
            else:
                left = mid + 1
        
        return left