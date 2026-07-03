import functools
import itertools
import collections
from typing import List

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        mapping = collections.defaultdict(int)
        for count in range(1, len(nums) + 1):
            subsets = itertools.combinations(nums, count)
            for subset in subsets:
                or_val = functools.reduce(lambda a, b: a | b, subset)
                mapping[or_val] += 1
        return mapping[max(mapping.keys())]