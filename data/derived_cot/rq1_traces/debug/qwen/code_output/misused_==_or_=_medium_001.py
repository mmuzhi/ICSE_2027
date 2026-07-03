class Solution:
    def maxAbsValExpr(self, arr1: List[int], arr2: List[int]) -> int:
        n = len(arr1)
        min1, max1 = float('inf'), float('-inf')
        min2, max2 = float('inf'), float('-inf')
        min3, max3 = float('inf'), float('-inf')
        min4, max4 = float('inf'), float('-inf')
        
        for i in range(n):
            e1 = i + arr1[i] + arr2[i]
            e2 = i + arr1[i] - arr2[i]
            e3 = i - arr1[i] + arr2[i]
            e4 = i - arr1[i] - arr2[i]
            
            if e1 < min1:
                min1 = e1
            if e1 > max1:
                max1 = e1
            if e2 < min2:
                min2 = e2
            if e2 > max2:
                max2 = e2
            if e3 < min3:
                min3 = e3
            if e3 > max3:
                max3 = e3
            if e4 < min4:
                min4 = e4
            if e4 > max4:
                max4 = e4
        
        candidate1 = max(max1, -min1)
        candidate2 = max(max2, -min2)
        candidate3 = max(max3, -min3)
        candidate4 = max(max4, -min4)
        
        return max(candidate1, candidate2, candidate3, candidate4)