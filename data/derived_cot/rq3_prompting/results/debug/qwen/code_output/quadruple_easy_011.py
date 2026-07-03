class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        s = set(nums)
        candidates = [num for num in s if num > 0 and -num in s]
        return max(candidates) if candidates else -1