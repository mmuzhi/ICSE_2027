from typing import List

class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        each_sum = total // 3
        count = 0
        current_sum = 0
        for num in arr:
            current_sum += num
            if current_sum == each_sum:
                count += 1
                current_sum = 0
        return count >= 3