class Solution:
    def maximumGap(self, nums: list) -> int:
        if len(nums) < 2:
            return 0
        nums = sorted(nums)
        max_gap = 0
        for i in range(len(nums) - 1):
            current_gap = nums[i+1] - nums[i]
            if current_gap > max_gap:
                max_gap = current_gap
        return max_gap