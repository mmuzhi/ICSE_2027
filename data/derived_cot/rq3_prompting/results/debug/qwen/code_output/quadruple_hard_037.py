class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        
        from functools import lru_cache
        
        @lru_cache(maxsize=None)
        def dp(i, prev, ct, k):
            if k < 0:
                return float('inf')
            if i == n:
                if ct == 0:
                    return 0
                else:
                    if ct == 1:
                        return 1
                    else:
                        return 1 + len(str(ct))
            
            key = (i, prev, ct, k)
            if key in dp.cache:
                return dp.cache[key]
            
            if s[i] == prev:
                inc = dp(i+1, prev, ct+1, k)
            else:
                if ct == 0:
                    x = 0
                elif ct == 1:
                    x = 1
                else:
                    x = 1 + len(str(ct))
                inc = x + dp(i+1, s[i], 1, k)
            
            exc = dp(i+1, prev, ct, k-1)
            
            res = min(inc, exc)
            dp.cache[key] = res
            return res
        
        dp.cache = {}
        return dp(0, "", 0, k)