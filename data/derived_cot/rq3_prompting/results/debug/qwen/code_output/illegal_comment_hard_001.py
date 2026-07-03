class Solution:
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:
        n = len(nums)
        if n < 3:
            return 0
        dp = [0] * n
        dp[2] = 1
        total = 1
        for i in range(3, n):
            if nums[i] - nums[i-1] == nums[i-1] - nums[i-2]:
                dp[i] = dp[i-1] + 1
            else:
                dp[i] = 1
            total += dp[i]
        return total