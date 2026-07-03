from typing import List

class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        res = []
        cur = []
        
        def backtrack(i):
            if i == len(s) and len(cur) == 4:
                res.append(".".join(cur))
                return
            if len(cur) > 4 or i > len(s):
                return
            if i < len(s) and s[i] == '0':
                cur.append('0')
                backtrack(i + 1)
                cur.pop()
                return
            j = 0
            while j < 3 and i + j < len(s):
                num_str = s[i:i+j+1]
                if int(num_str) < 256:
                    cur.append(num_str)
                    backtrack(i + j + 1)
                    cur.pop()
                j += 1
        
        backtrack(0)
        return res