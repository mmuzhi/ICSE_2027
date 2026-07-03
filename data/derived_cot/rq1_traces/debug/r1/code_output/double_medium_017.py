import collections
import itertools
import functools
from typing import List

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        mapping = collections.defaultdict(int)
        for count in range(1, len(nums)+1):
            subsets = list(itertools.combinations(nums, count))
            for ele in subsets:
                or_val = functools.reduce(lambda a, b: a | b, list(ele), 0)
                mapping[or_val] += 1
        return mapping[max(mapping.keys())]