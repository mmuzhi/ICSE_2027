from typing import List

class Solution:
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:
        n = len(arr1)
        val1 = [i + arr1[i] + arr2[i] for i in range(n)]
        val2 = [i + arr1[i] - arr2[i] for i in range(n)]
        val3 = [i - arr1[i] + arr2[i] for i in range(n)]
        val4 = [i - arr1[i] - arr2[i] for i in range(n)]
        candidates = []
        for lst in [val1, val2, val3, val4]:
            if lst:
                max_val = max(lst)
                min_val = min(lst)
                candidates.append(max(max_val, -min_val))
        return max(candidates) if candidates else 0