class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        if not nums:
            return -1
        return -min(nums)