class Solution:
    def numberOfGoodSubarraySplits(self, nums: List[int]) -> int:
        if 1 not in nums:
            return 0
        
        positions = [i for i, x in enumerate(nums) if x == 1]
        n = len(positions)
        
        if n == 0:
            return 0
        if n == 1:
            return 1
        
        result = 1
        for i in range(n-1):
            ways = positions[i+1] - positions[i] + 1
            result = (result * ways) % 1000000007
        
        return result