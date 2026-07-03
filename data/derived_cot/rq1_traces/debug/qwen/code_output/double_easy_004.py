from collections import defaultdict

class Solution:
    def findLHS(self, nums: List[int]) -> int:
        count_map = defaultdict(int)
        for num in nums:
            count_map[num] += 1
        
        if not count_map:
            return 0
        
        keys = sorted(count_map.keys())
        dp = {}
        result = 0
        
        for key in keys:
            if key - 1 in count_map:
                dp[key] = dp[key - 1] + count_map[key]
            else:
                dp[key] = count_map[key]
            if dp[key] > result:
                result = dp[key]
        
        return result