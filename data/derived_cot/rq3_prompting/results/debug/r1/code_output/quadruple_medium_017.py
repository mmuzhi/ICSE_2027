from typing import List

class Solution:
    def satisfiesTrip(self, mid: int, time: List[int], totalTrip: int) -> bool:
        trip = 0
        for t in time:
            trip += mid // t
        return trip >= totalTrip

    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        left = min(time)
        right = left * totalTrips
        while left < right:
            mid = (left + right) // 2
            if self.satisfiesTrip(mid, time, totalTrips):
                right = mid
            else:
                left = mid + 1
        return left