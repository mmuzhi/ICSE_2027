class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        memo = {}
        
        def dp(i, prev, ct, k):
            if k < 0:
                return float('inf')
            if i == n:
                if ct > 1:
                    return len(str(ct)) + 1
                elif ct == 1:
                    return 1
                else:
                    return 0
            key = (i, prev, ct, k)
            if key in memo:
                return memo[key]
            # include current character
            if s[i] == prev:
                inc = dp(i+1, prev, ct+1, k)
            else:
                # compute length of previous run
                x = 0
                if ct > 1:
                    x = len(str(ct)) + 1
                elif ct == 1:
                    x = 1
                inc = x + dp(i+1, s[i], 1, k)
            # exclude current character (delete it)
            exc = dp(i+1, prev, ct, k-1)
            res = min(inc, exc)
            memo[key] = res
            return res
        
        return dp(0, "", 0, k)