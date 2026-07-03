import functools
import itertools
import collections

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        mapping = collections.defaultdict(int)
        n = len(nums)
        if n == 0:
            return 0
        for count in range(1, n+1):
            for ele in itertools.combinations(nums, count):
                key = functools.reduce(lambda a, b: a | b, ele)
                mapping[key] += 1
        if not mapping:
            return 0
        max_key = max(mapping.keys())
        return mapping[max_key]