class Solution:
    def dp(self, i, s, prev, k, ct, n, dct):
        if i >= n:
            x = 0
            if ct > 1:
                x = len(str(ct)) + 1
            elif ct == 1:
                x = 1
            return x
        
        if (i, prev, ct, k) in dct:
            return dct[(i, prev, ct, k)]
        
        res = float('inf')
        
        if s[i] == prev:
            inc = self.dp(i+1, s, prev, k, ct+1, n, dct)
            res = min(res, inc)
            if k >= 1:
                exc = self.dp(i+1, s, prev, k-1, ct-1, n, dct)
                res = min(res, exc)
        else:
            x = 0
            if ct > 1:
                x = len(str(ct)) + 1
            elif ct == 1:
                x = 1
            inc = x + self.dp(i+1, s, s[i], k, 1, n, dct)
            res = min(res, inc)
            if k >= 1:
                exc = self.dp(i+1, s, prev, k-1, ct, n, dct)
                res = min(res, exc)
        
        dct[(i, prev, ct, k)] = res
        return res

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        return self.dp(0, s, "", k, 0, n, {})