class Solution:
    def satisfiesTrip(self, mid, time, totalTrips):
        trip = 0
        for t in time:
            trip += mid // t
        if trip >= totalTrips:
            return True
        return False

    def minimumTime(self, time: List[int], totalTrips: int) -> int:
        minimum = min(time)
        left = minimum
        right = minimum * totalTrips
        while left < right:
            mid = (left + right) // 2
            if self.satisfiesTrip(mid, time, totalTrips):
                right = mid
            else:
                left = mid + 1
        return right