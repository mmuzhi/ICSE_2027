class Solution:
    def maxPower(self, stations: List[int], r: int, k: int) -> int:
        start, end = min(stations), sum(stations) + k
        while start + 1 < end:
            mid = (start + end) // 2
            if self.check(stations, r, k, mid):
                start = mid
            else:
                end = mid
        if self.check(stations, r, k, end):
            return end
        else:
            return start
    
    def check(self, stations, r, k, target):
        n = len(stations)
        stations_copy = stations[:]
        k_remaining = k
        power = sum(stations_copy[:r])
        ans = True
        for i in range(n + 1):
            if i + r < n:
                power += stations_copy[i + r]
            if i - r - 1 >= 0:
                power -= stations_copy[i - r - 1]
            if power >= target:
                continue
            elif power + k_remaining < target:
                ans = False
                break
            else:
                diff = target - power
                power = target
                index = min(i + r, n - 1)
                stations_copy[index] += diff
                k_remaining -= diff
        return ans