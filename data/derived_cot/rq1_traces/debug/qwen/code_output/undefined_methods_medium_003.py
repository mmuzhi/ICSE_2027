class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        def check(x):
            total = 0
            for ele in piles:
                total += (ele + x - 1) // x
            return total <= h
        
        l = 1
        r = max(piles)
        while l < r:
            mid = (l + r) // 2
            if check(mid):
                r = mid
            else:
                l = mid + 1
        return l