class Solution:
    def thirdMax(self, nums) -> int:
        s = set(nums)
        return max(s) if len(s) < 3 else sorted(s)[-3]