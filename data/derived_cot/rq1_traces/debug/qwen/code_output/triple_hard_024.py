class Solution:
    def dp(self, i, s, prev, k, ct, n, dct):
        if k < 0:
            return float('inf')
        if i == n:
            if ct == 0:
                return 0
            if ct == 1:
                return 1
            return len(str(ct)) + 1
        
        key = (i, prev, ct, k)
        if key in dct:
            return dct[key]
        
        remove_cost = float('inf')
        if k > 0:
            remove_cost = self.dp(i+1, s, prev, k-1, ct, n, dct)
        
        if s[i] == prev:
            keep_cost = self.dp(i+1, s, prev, k, ct+1, n, dct)
        else:
            x = 0
            if ct == 0:
                x = 0
            elif ct == 1:
                x = 1
            else:
                x = len(str(ct)) + 1
            keep_cost = x + self.dp(i+1, s, s[i], k, 1, n, dct)
        
        total = min(remove_cost, keep_cost)
        dct[key] = total
        return total

    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        return self.dp(0, s, "", k, 0, n, {})