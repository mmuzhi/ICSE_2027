class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        s = set(nums)
        nums.sort(reverse=True)
        for i in range(len(nums)):
            if -nums[i] in s:
                return nums[i]
        return -1