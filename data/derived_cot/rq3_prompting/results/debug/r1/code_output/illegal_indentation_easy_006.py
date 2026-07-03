from typing import List

class Solution:
    def thirdMax(self, nums: List[int]) -> int:
        unique = list(set(nums))
        if len(unique) < 3:
            return max(unique)
        else:
            return sorted(unique)[-3]