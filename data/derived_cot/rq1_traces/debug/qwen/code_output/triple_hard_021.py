class Solution:
    def getLengthOfOptimalCompression(self, s: str, k: int) -> int:
        n = len(s)
        dct = {}
        
        def dp(i, prev, k, ct):
            if k < 0:
                return float('inf')
            if i >= n:
                if ct == 0:
                    return 0
                elif ct == 1:
                    return 1
                else:
                    return len(str(ct)) + 1
            
            key = (i, prev, k, ct)
            if key in dct:
                return dct[key]
            
            if s[i] == prev:
                keep = dp(i+1, prev, k, ct+1)
            else:
                if ct == 0:
                    keep = dp(i+1, s[i], k, 1)
                else:
                    if ct == 1:
                        cost = 1
                    else:
                        cost = len(str(ct)) + 1
                    keep = cost + dp(i+1, s[i], k, 1)
            
            remove = dp(i+1, prev, k-1, ct)
            ans = min(keep, remove)
            dct[key] = ans
            return ans
        
        return dp(0, "", k, 0)