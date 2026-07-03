class Solution:
    def dp(self, i, s, prev, k, ct, n, dct):
        if k < 0:
            return float("inf")
        if i >= n:
            if ct == 0:
                return 0
            if ct == 1:
                return 1
            else:
                return len(str(ct)) + 1
        if (i, prev, ct, k) in dct:
            return dct[(i, prev, ct, k)]
        res = float('inf')
        if s[i] == prev:
            res = self.dp(i+1, s, prev, k, ct+1, n, dct)
        else:
            if ct == 0:
                cost_here = 0
            else:
                if ct == 1:
                    cost_here = 1
                else:
                    cost_here = len(str(ct)) + 1
            res = cost_here + self.dp(i+1, s, s[i], k, 1, n, dct)
        if k > 0:
            res = min(res, self.dp(i+1, s, prev, k-1, ct, n, dct))
        dct[(i, prev, ct, k)] = res
        return res

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        return self.dp(0, s, "", k, 0, n, {})