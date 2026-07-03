class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        s = set(nums)
        candidate = -1
        for num in nums:
            if (-num) in s:
                candidate = max(candidate, num)
        return candidate