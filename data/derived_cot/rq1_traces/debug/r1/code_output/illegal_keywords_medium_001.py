from functools import reduce
from typing import List

class Solution:
    def numberOfGoodSubarraySplits(self, nums: List[int]) -> int:
        if 1 not in nums:
            return 0
        nums_str = ''.join(map(str, nums)).strip('0')
        parts = nums_str.split('1')
        factors = [1 + len(part) for part in parts]
        return reduce(lambda a, b: a * b, factors) % 1000000007