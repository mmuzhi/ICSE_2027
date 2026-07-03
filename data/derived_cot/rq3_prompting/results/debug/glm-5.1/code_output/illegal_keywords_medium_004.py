from typing import List

class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        n = len(nums)
        min_val, max_val = float('inf'), float('-inf')
        min_L, min_R, max_L, max_R = -1, -1, -1, -1
        
        for i, x in enumerate(nums):
            if x < min_val:
                min_val = x
                min_L = min_R = i
            elif x == min_val:
                min_R = i
                
            if x > max_val:
                max_val = x
                max_L = max_R = i
            elif x == max_val:
                max_R = i
                
        def calc(i, j):
            return min(min(i + 1, n - i) + min(j + 1, n - j), max(i + 1, j + 1), max(n - i, n - j))
            
        return min(calc(min_L, max_L), calc(min_L, max_R), calc(min_R, max_L), calc(min_R, max_R))