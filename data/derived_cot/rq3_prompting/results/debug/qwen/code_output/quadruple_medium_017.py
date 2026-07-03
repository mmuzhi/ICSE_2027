class Solution:
    def satisfiesTrip(self, mid, time, totalTrips):
        trip = 0
        for t in time:
            trip += mid // t
        if trip >= totalTrips:
            return False
        return True

    def minimumTime(self, time, totalTrips):
        time.sort(reverse=True)
        left = 1
        right = min(time) * totalTrips
        while left < right:
            mid = (left + right) // 2
            if self.satisfiesTrip(mid, time, totalTrips):
                right = mid
            else:
                left = mid + 1
        return right