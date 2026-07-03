from collections import defaultdict, Counter
from typing import List

class Solution:
    def numberOfArithmeticSlices(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        dp = defaultdict(Counter)
        for i in range(1, n):
            for j in range(i):
                d = nums[i] - nums[j]
                cnt = dp[j][d]  # number of subsequences ending at j with diff d (length >=2)
                ans += cnt      # appending nums[i] makes them length >=3
                dp[i][d] += cnt + 1  # +1 for the new length-2 subsequence (j,i)
        return ans