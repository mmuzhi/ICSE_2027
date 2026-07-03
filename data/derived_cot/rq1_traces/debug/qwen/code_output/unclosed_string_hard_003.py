class Solution:
    def dp(self, i, s, prev, ct, k, n, dct):
        if k < 0:
            return float('inf')
        if i >= n:
            if ct == 0:
                return 0
            if ct == 1:
                return 1
            else:
                return len(str(ct)) + 1
        
        key = (i, prev, ct, k)
        if key in dct:
            return dct[key]
        
        res = float('inf')
        if k > 0:
            res = min(res, self.dp(i+1, s, prev, ct, k-1, n, dct))
        
        if s[i] == prev:
            res = min(res, self.dp(i+1, s, prev, ct+1, k, n, dct))
        else:
            cost = 0
            if ct == 1:
                cost = 1
            elif ct > 1:
                cost = len(str(ct)) + 1
            res = min(res, cost + self.dp(i+1, s, s[i], 1, k, n, dct))
        
        dct[key] = res
        return res

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        return self.dp(0, s, "", 0, k, n, {})