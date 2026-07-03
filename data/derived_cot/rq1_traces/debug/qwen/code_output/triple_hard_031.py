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
                    return len(str(ct)) + 1
        if (i, prev, ct, k) in dct:
            return dct[(i, prev, ct, k)]
        
        res = []
        if k > 0:
            res.append(self.dp(i+1, s, prev, k-1, ct, n, dct))
        
        if s[i] == prev and ct > 0:
            res.append(self.dp(i+1, s, prev, k, ct+1, n, dct))
        
        if ct == 0:
            x = 0
        else:
            if ct == 1:
                x = 1
            else:
                x = len(str(ct)) + 1
        res.append(x + self.dp(i+1, s, s[i], k, 1, n, dct))
        
        best = min(res) if res else float('inf')
        dct[(i, prev, ct, k)] = best
        return best

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        return self.dp(0, s, "", k, 0, n, {})