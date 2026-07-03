class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        memo = {}
        
        def dp(i: int, prev: str, k: int, ct: int) -> int:
            if k < 0:
                return float('inf')
            if i >= n:
                if ct > 1:
                    return len(str(ct)) + 1
                elif ct == 1:
                    return 1
                else:
                    return 0
            key = (i, prev, ct, k)
            if key in memo:
                return memo[key]
            
            # keep current character
            if s[i] == prev:
                inc = dp(i + 1, prev, k, ct + 1)
            else:
                # length contributed by the previous run
                x = 0
                if ct > 1:
                    x = len(str(ct)) + 1
                elif ct == 1:
                    x = 1
                inc = x + dp(i + 1, s[i], k, 1)
            
            # delete current character
            exc = dp(i + 1, prev, k - 1, ct)
            
            memo[key] = min(inc, exc)
            return memo[key]
        
        return dp(0, '', k, 0)