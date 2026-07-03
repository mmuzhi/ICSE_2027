class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        if n == 0:
            return True
        dp = [False] * (n + 1)
        dp[0] = True
        if n >= 1:
            dp[1] = True
        if n >= 2:
            dp[2] = (nums[0] == nums[1])
        for i in range(3, n + 1):
            dp[i] = dp[i - 1] or (dp[i - 2] and nums[i - 2] == nums[i - 1]) or (dp[i - 3] and nums[i - 3] + 1 == nums[i - 2] and nums[i - 2] + 1 == nums[i - 1])
        return dp[n]