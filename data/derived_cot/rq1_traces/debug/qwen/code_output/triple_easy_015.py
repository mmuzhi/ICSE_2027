class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        s = set(nums)
        candidates = [x for x in s if x > 0 and -x in s]
        return max(candidates) if candidates else -1