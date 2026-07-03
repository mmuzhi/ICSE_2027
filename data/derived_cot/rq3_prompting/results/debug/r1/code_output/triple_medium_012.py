class Solution:
    def maximumGap(self, nums: list) -> int:
        nums = sorted(nums)
        max_gap = float("-inf")
        if len(nums) < 2:
            return 0
        for i in range(len(nums) - 1):
            diff = abs(nums[i] - nums[i + 1])
            if max_gap < diff:
                max_gap = diff
        return max_gap