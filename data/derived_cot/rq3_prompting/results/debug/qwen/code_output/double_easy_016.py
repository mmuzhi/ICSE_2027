class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        nums = sorted(nums, reverse=True)
        for i in range(len(nums)):
            return nums[i]
        return -1