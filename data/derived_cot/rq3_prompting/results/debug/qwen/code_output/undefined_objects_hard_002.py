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
        if n == 0:
            return target <= 0 and k >= 0
        
        if r > n:
            return target <= sum(stations) + k and k >= 0
        
        add = [0] * n
        total_add = 0
        curr = sum(stations[:r])
        
        for i in range(n - r + 1):
            if i + r < n:
                curr += stations[i + r]
            if i - r - 1 >= 0:
                curr -= stations[i - r - 1]
            if curr < target:
                deficit = target - curr
                if deficit > k:
                    return False
                if i + r < n:
                    add[i + r] += deficit
                    total_add += deficit
                    curr += deficit
                else:
                    add[i] += deficit
                    total_add += deficit
                    curr += deficit
        
        return True