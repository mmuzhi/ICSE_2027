from typing import List

class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        n = len(nums)
        i_min = nums.index(min(nums))
        i_max = nums.index(max(nums))
        left_min = i_min + 1
        right_min = n - i_min
        left_max = i_max + 1
        right_max = n - i_max
        return min(
            max(left_min, left_max),
            max(right_min, right_max),
            left_min + right_max,
            left_max + right_min
        )