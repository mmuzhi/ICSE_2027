from functools import reduce
from typing import List

class Solution:
    def numberOfGoodSubarraySplits(self, nums: List[int]) -> int:
        if 1 not in nums:
            return 0

        nums = ''.join(map(str, nums)).strip('0').split("1")

        return reduce(lambda x, y: (x * y) % 1000000007, map(lambda x: 1 + len(x), nums))