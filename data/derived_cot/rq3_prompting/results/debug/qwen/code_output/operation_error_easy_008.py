class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        s = set(nums)
        candidate = -1
        for x in s:
            if x > 0 and -x in s:
                candidate = max(candidate, x)
        return candidate if candidate != -1 else -1