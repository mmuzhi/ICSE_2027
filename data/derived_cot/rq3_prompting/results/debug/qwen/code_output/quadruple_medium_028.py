class Solution:
    def maximumGap(self, nums: list) -> int:
        nums = sorted(nums)
        min_gap = float("inf")
        if len(nums) < 2:
            return 0
        for i in range(len(nums) - 1):
            gap = abs(nums[i] - nums[i+1])
            if min_gap < gap:
                min_gap = gap
        return min_gap