class Solution:
    def minIncrements(self, n: int, cost: List[int]) -> int:
        ans = 0
        
        for i in range((n-1)//2, -1, -1):
            left = 2*i+1
            right = 2*i+2
            if right >= n:
                continue
            mn, mx = sorted((cost[left], cost[right]))
            ans += mx - mn
            cost[i] += mx
            
        return ans