import math

class Solution:
    def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
        n = len(dist)
        if n - 1 > hour:
            return -1
        
        left, right = 1, 10**18
        
        while left < right:
            mid = (left + right) // 2
            total_time = 0.0
            for d in dist[:-1]:
                total_time += math.ceil(d / mid)
            total_time += dist[-1] / mid
            
            if total_time <= hour:
                right = mid
            else:
                left = mid + 1
        
        return left