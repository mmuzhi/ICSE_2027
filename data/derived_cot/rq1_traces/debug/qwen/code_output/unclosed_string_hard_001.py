class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        def cost_segment(t):
            i, j = 0, len(t) - 1
            c = 0
            while i < j:
                if t[i] != t[j]:
                    c += 1
                i += 1
                j -= 1
            return c
        
        dp = {}
        
        def A(s, k):
            if (s, k) in dp:
                return dp[(s, k)]
            
            if k == 0:
                return 0
            if k == 1:
                return cost_segment(s)
            
            f = float('inf')
            for x in range(1, len(s)):
                cost_here = cost_segment(s[:x])
                rest_cost = A(s[x:], k-1)
                if rest_cost != float('inf'):
                    f = min(f, cost_here + rest_cost)
            
            dp[(s, k)] = f
            return f
        
        return A(s, k)