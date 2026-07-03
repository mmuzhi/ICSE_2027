class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dp(i, prev, ct, k_left):
            if k_left < 0:
                return float('inf')
            if i >= n:
                if ct > 0:
                    return 1 + len(str(ct))
                else:
                    return 0
            
            remove_val = dp(i+1, prev, ct, k_left-1) if k_left >= 0 else float('inf')
            
            if s[i] == prev:
                keep_val = dp(i+1, prev, ct+1, k_left)
            else:
                if ct > 0:
                    keep_val = 1 + len(str(ct)) + dp(i+1, s[i], 1, k_left)
                else:
                    keep_val = dp(i+1, s[i], 1, k_left)
            
            return min(remove_val, keep_val)
        
        return dp(0, "", 0, k)