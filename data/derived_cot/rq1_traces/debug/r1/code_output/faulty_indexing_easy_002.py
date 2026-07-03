class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        nums = sorted(nums, reverse=True)
        s = set(nums)
        for num in nums:
            if num <= 0:
                break
            if -num in s:
                return num
        return -1