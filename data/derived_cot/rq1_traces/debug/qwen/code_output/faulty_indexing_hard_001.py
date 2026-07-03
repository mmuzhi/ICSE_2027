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
        if target == 0:
            return True
        arr = stations + stations
        add = [0] * n
        remaining = k
        for start in range(n):
            current = 0
            for i in range(start, start + r):
                current += arr[i] + add[i % n]
            if current < target:
                deficit = target - current
                if deficit > remaining:
                    return False
                remaining -= deficit
                add[start % n] += deficit
        return remaining >= 0