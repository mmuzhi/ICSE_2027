import functools
import collections
import itertools

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        if not nums:
            return 0
        mapping = collections.defaultdict(int)
        n = len(nums)
        for count in range(1, n + 1):
            for ele in itertools.combinations(nums, count):
                or_value = functools.reduce(lambda a, b: a | b, ele)
                mapping[or_value] += 1
        return mapping[max(mapping.keys())]