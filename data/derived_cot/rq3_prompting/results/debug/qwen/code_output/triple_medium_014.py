class Solution:
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:
        n = len(arr1)
        val1 = []
        val2 = []
        val3 = []
        val4 = []
        for i in range(n):
            val1.append(i + arr1[i] + arr2[i])
            val2.append(i + arr1[i] - arr2[i])
            val3.append(i - arr1[i] + arr2[i])
            val4.append(i - arr1[i] - arr2[i])
        
        max_abs_val1 = max(max(val1), -min(val1))
        max_abs_val2 = max(max(val2), -min(val2))
        max_abs_val3 = max(max(val3), -min(val3))
        max_abs_val4 = max(max(val4), -min(val4))
        
        ans = max(max_abs_val1, max_abs_val2, max_abs_val3, max_abs_val4)
        return ans