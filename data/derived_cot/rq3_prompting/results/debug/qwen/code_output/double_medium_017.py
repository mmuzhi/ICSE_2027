import functools
import collections
import itertools
from typing import List

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        mapping = collections.defaultdict(int)
        n = len(nums)
        for count in range(1, n+1):
            for subset in itertools.combinations(nums, count):
                or_val = functools.reduce(lambda a, b: a | b, subset)
                mapping[or_val] += 1
        if not mapping:
            return 0
        max_count = max(mapping.values())
        return max_count