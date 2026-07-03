from typing import List

class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        if len(nums) < 3:
            return len(nums)

        p1, p2 = 1, 2

        while p2 < len(nums):
            # Check if nums[p2] would create a third duplicate
            if nums[p2] == nums[p1] and nums[p1] == nums[p1 - 1]:
                # Skip all occurrences of this value
                while p2 < len(nums) and nums[p2] == nums[p1]:
                    p2 += 1
            else:
                p1 += 1
                nums[p1] = nums[p2]
                p2 += 1

        return p1 + 1