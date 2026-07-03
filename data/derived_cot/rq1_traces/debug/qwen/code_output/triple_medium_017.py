from typing import List

class Solution:
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:
        n = len(arr1)
        if n == 0:
            return 0
        
        val1, val2, val3, val4 = [], [], [], []
        for i in range(n):
            val1.append(i + arr1[i] + arr2[i])
            val2.append(i + arr1[i] - arr2[i])
            val3.append(i - arr1[i] + arr2[i])
            val4.append(i - arr1[i] - arr2[i])
        
        candidate1 = max(max(val1), -min(val1))
        candidate2 = max(max(val2), -min(val2))
        candidate3 = max(max(val3), -min(val3))
        candidate4 = max(max(val4), -min(val4))
        
        return max(candidate1, candidate2, candidate3, candidate4)