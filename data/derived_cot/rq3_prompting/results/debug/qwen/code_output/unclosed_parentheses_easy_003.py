from collections import defaultdict

class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        count = defaultdict(int)
        for num in nums:
            count[num] += 1
        
        keys = sorted(count.keys())
        prefix = 0
        cum = {}
        for key in keys:
            cum[key] = prefix
            prefix += count[key]
        
        res = []
        for num in nums:
            res.append(cum[num])
        return res