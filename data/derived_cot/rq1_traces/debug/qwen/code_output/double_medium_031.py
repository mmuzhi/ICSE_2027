from typing import List

class Solution:
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:
        val1, val2, val3, val4 = [], [], [], []
        for i in range(len(arr1)):
            val1.append(i + arr1[i] + arr2[i])
            val2.append(i + arr1[i] - arr2[i])
            val3.append(i - arr1[i] + arr2[i])
            val4.append(i - arr1[i] - arr2[i])
        
        def computeMaxAbs(arr):
            return max(max(arr), abs(min(arr)))
        
        ans = 0
        ans = max(ans, computeMaxAbs(val1))
        ans = max(ans, computeMaxAbs(val2))
        ans = max(ans, computeMaxAbs(val3))
        ans = max(ans, computeMaxAbs(val4))
        return ans