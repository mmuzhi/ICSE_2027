from typing import List

class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        each_sum = total // 3
        if total % 3 != 0:
            return False
        sumi = 0
        count = 0
        for x in arr:
            sumi += x
            if count < 2 and sumi == each_sum:
                sumi = 0
                count += 1
        return count == 2 and sumi == each_sum