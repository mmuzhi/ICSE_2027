from typing import List

class Solution:
    def maximumNumber(self, num: str, change: List[int]) -> str:
        num = list(num)
        on = False
        for i, ch in enumerate(num):
            d = int(ch)
            if change[d] > d:
                on = True
                num[i] = str(change[d])
            elif on and change[d] < d:
                break
        return "".join(num)