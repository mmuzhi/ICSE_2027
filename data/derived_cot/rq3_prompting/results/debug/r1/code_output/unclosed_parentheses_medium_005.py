from typing import List

class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        if n < 2:
            return False
        
        # Rolling DP: checks = (dp[i-2], dp[i-1], dp[i])
        checks = (True, False, nums[0] == nums[1])
        
        for i in range(2, n):
            curr = nums[i]
            prev1 = nums[i-1]
            prev2 = nums[i-2]
            
            new_dp = (checks[1] and curr == prev1) or \
                     (checks[0] and curr == prev1 == prev2) or \
                     (checks[0] and curr == prev1 + 1 == prev2 + 2)
            
            checks = (checks[1], checks[2], new_dp)
        
        return checks[2]