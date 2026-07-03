from typing import List

class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        min_val = min(nums)
        max_val = max(nums)
        if min_val == max_val:
            return len(nums)
        i_min = nums.index(min_val)
        i_max = nums.index(max_val)
        option1 = max(i_min + 1, i_max + 1)
        option2 = max(len(nums) - i_min, len(nums) - i_max)
        option3 = (i_min + 1) + (len(nums) - i_max) if i_min < i_max else (i_max + 1) + (len(nums) - i_min)
        return min(option1, option2, option3)