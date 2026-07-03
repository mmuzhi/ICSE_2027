from typing import List

class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        res = []
        cur = []
        
        def backtrack(i: int):
            if i == len(s) and len(cur) == 4:
                res.append(".".join(cur))
                return
            if i >= len(s) or len(cur) >= 4:
                return
            if s[i] == '0':
                cur.append(s[i])
                backtrack(i + 1)
                cur.pop()
                return
            # Try segments of length 1, 2, 3
            for j in range(3):
                if i + j >= len(s):
                    break
                part = s[i:i + j + 1]
                if int(part) <= 255:
                    cur.append(part)
                    backtrack(i + j + 1)
                    cur.pop()
                else:
                    # Larger numbers will only get bigger, so stop
                    break
        
        backtrack(0)
        return res