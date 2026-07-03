class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        def dp(i, prev, ct, k_left, memo):
            if k_left < 0:
                return float('inf')
            if i >= n:
                if ct == 0:
                    return 0
                if ct == 1:
                    return 1
                return len(str(ct)) + 1
            key = (i, prev, ct, k_left)
            if key in memo:
                return memo[key]
            exc = dp(i+1, prev, ct, k_left-1, memo)
            if s[i] == prev:
                inc = dp(i+1, prev, ct+1, k_left, memo)
            else:
                cost = 0
                if ct > 1:
                    cost = len(str(ct)) + 1
                elif ct == 1:
                    cost = 1
                inc = cost + dp(i+1, s[i], 1, k_left, memo)
            ans = min(inc, exc)
            memo[key] = ans
            return ans

        return dp(0, '', 0, k, {})