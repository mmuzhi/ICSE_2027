from typing import List

class Solution:
    def minimumDeletions(self, nums: List[int]) -> int:
        distinct = len(set(nums))
        return len(nums) - distinct