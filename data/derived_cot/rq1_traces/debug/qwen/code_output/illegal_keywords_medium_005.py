from typing import List

class Solution:
    def findValueOfPartition(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        nums.sort()
        min_diff = float('inf')
        for i in range(1, len(nums)):
            min_diff = min(min_diff, abs(nums[i] - nums[i-1]))
        return min_diff if min_diff != float('inf') else 0