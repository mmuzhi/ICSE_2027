class Solution:
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:
        val1 = []
        val2 = []
        val3 = []
        val4 = []
        n = len(arr1)
        for i in range(n):
            val1.append(i + arr1[i] + arr2[i])
            val2.append(i + arr1[i] - arr2[i])
            val3.append(i - arr1[i] + arr2[i])
            val4.append(i - arr1[i] - arr2[i])
        ans = 0
        if val1:
            ans = max(val1) - min(val1)
        if val2 and (ans > max(val2) - min(val2)):
            ans = max(val2) - min(val2)
        if val3 and (ans > max(val3) - min(val3)):
            ans = max(val3) - min(val3)
        if val4 and (ans > max(val4) - min(val4)):
            ans = max(val4) - min(val4)
        return ans