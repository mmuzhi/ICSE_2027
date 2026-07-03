class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        from functools import lru_cache

        @lru_cache(None)
        def dp(i: int, prev: str, ct: int, k: int) -> int:
            if k < 0:
                return float('inf')
            if i == n:
                if ct == 0:
                    return 0
                if ct == 1:
                    return 1
                return len(str(ct)) + 1

            # Option 1: include current character
            if s[i] == prev:
                inc = dp(i + 1, prev, ct + 1, k)
            else:
                # finish previous run
                add = 0
                if ct == 1:
                    add = 1
                elif ct > 1:
                    add = len(str(ct)) + 1
                inc = add + dp(i + 1, s[i], 1, k)

            # Option 2: delete current character
            exc = dp(i + 1, prev, ct, k - 1)

            return min(inc, exc)

        # Use a dummy initial prev that will never match a letter
        return dp(0, '', 0, k)