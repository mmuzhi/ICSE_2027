from typing import List

class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        res = []
        cur = []

        def backtrack(i: int):
            if i == len(s):
                if len(cur) == 4:
                    res.append(".".join(cur))
                return
            if len(cur) >= 4:
                return
            if s[i] == '0':
                cur.append(s[i])
                backtrack(i + 1)
                cur.pop()
                return
            j = 0
            while j < 3 and i + j < len(s):
                seg = s[i:i + j + 1]
                if int(seg) < 256:
                    cur.append(seg)
                    backtrack(i + j + 1)
                    cur.pop()
                j += 1

        backtrack(0)
        return res