class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        if n == 0:
            return True
        if n == 1:
            return False
        if n == 2:
            return nums[0] == nums[1]
        if n == 3:
            return (nums[0] == nums[1] == nums[2]) or (nums[0] + 1 == nums[1] and nums[1] + 1 == nums[2])
        
        dp = [False] * (n + 1)
        dp[0] = True
        dp[1] = False
        dp[2] = (nums[0] == nums[1])
        dp[3] = (nums[0] == nums[1] == nums[2]) or (nums[0] + 1 == nums[1] and nums[1] + 1 == nums[2])
        
        for i in range(4, n + 1):
            if dp[i-2] and nums[i-1] == nums[i-2]:
                dp[i] = True
            elif dp[i-3] and (nums[i-1] == nums[i-2] == nums[i-3] or (nums[i-3] + 1 == nums[i-2] and nums[i-2] + 1 == nums[i-1])):
                dp[i] = True
            else:
                dp[i] = False
        
        return dp[n]