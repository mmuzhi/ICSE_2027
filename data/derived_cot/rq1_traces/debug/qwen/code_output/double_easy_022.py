class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        sorted_nums = sorted(nums, reverse=True)
        s = set(nums)
        for num in sorted_nums:
            if -num not in s:
                return num
        return -1