from bisect import bisect_left
from collections import defaultdict

class Solution:
    def smallerNumbersThanCurrent(self, nums: List[int]) -> List[int]:
        freq = defaultdict(int)
        for num in nums:
            freq[num] += 1
        
        keys = sorted(freq.keys())
        prefix = []
        for key in keys:
            if prefix:
                prefix.append(prefix[-1] + freq[key])
            else:
                prefix.append(freq[key])
        
        res = []
        for num in nums:
            idx = bisect_left(keys, num)
            if idx == 0:
                res.append(0)
            else:
                res.append(prefix[idx-1])
        return res