from typing import List

class Solution:
    def selfDividingNumbers(self, left: int, right: int) -> List[int]:
        res = []
        for i in range(left, right):
            ch = True
            for j in str(i):
                if j == '0':
                    ch = False
                    break
                digit = int(j)
                if i % digit != 0:
                    ch = False
                    break
            if ch:
                res.append(i)
        return res