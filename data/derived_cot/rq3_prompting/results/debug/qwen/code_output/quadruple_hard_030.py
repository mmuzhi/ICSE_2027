class Solution:
    def dp(self, i, s, prev, k, ct, n, dct):
        if k < 0:
            return float('inf')
        if i >= n:
            if ct == 0:
                return 0
            else:
                if ct == 1:
                    return 1
                else:
                    return 1 + len(str(ct))
        if (i, prev, k, ct) in dct:
            return dct[(i, prev, k, ct)]
        
        res = float('inf')
        if k > 0:
            res = min(res, self.dp(i+1, s, prev, k-1, ct, n, dct))
        if s[i] == prev:
            new_ct = ct + 1
            res = min(res, self.dp(i+1, s, prev, k, new_ct, n, dct))
        else:
            x = 0
            if ct > 1:
                x = 1 + len(str(ct))
            elif ct == 1:
                x = 1
            else:
                x = 0
            res = min(res, x + self.dp(i+1, s, s[i], k, 1, n, dct))
        
        dct[(i, prev, k, ct)] = res
        return res

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        return self.dp(0, s, "", k, 0, n, {})