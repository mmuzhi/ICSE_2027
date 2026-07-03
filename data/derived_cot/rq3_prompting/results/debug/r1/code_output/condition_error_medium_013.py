from typing import List

class Solution:
    def minPairSum(self, nums: List[int]) -> int:
        nums.sort()
        left, right = 0, len(nums) - 1
        max_sum = 0
        while left < right:
            current_sum = nums[left] + nums[right]
            if current_sum > max_sum:
                max_sum = current_sum
            left += 1
            right -= 1
        return max_sum