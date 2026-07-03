from typing import List

class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        each_sum = total // 3
        cum_sum = 0
        first_part = False
        for i in range(len(arr)):
            cum_sum += arr[i]
            if not first_part and cum_sum == each_sum:
                first_part = True
            elif first_part and cum_sum == 2 * each_sum:
                if i != len(arr) - 1:
                    return True
        return False