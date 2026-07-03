class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dp(i, prev, ct, k_remaining):
            if i >= n:
                if ct == 0:
                    return 0
                if ct == 1:
                    return 1
                return 1 + len(str(ct))
            
            res_skip = float('inf')
            if k_remaining > 0:
                res_skip = dp(i+1, prev, ct, k_remaining-1)
            
            res_keep = float('inf')
            if prev == s[i]:
                res_keep = dp(i+1, s[i], ct+1, k_remaining)
            else:
                if ct == 0:
                    cost_prev = 0
                elif ct == 1:
                    cost_prev = 1
                else:
                    cost_prev = 1 + len(str(ct))
                res_keep = cost_prev + dp(i+1, s[i], 1, k_remaining)
            
            return min(res_skip, res_keep)
        
        return dp(0, '', 0, k)