from typing import List
from functools import reduce

class Solution:
    def numberOfGoodSubarraySplits(self, nums: List[int]) -> int:
        if 1 not in nums:
            return 0
        s = ''.join(map(str, nums)).strip('0')
        pieces = s.split('1')
        MOD = 1000000007
        ans = 1
        for p in pieces:
            ans = (ans * (len(p) + 1)) % MOD
        return ans