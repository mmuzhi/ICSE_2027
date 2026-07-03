import itertools
import functools

class Solution:
    def countMaxOrSubsets(self, nums: List[int]) -> int:
        if not nums:
            return 0
        total_or = 0
        for num in nums:
            total_or |= num
        count = 0
        n = len(nums)
        for r in range(1, n+1):
            for subset in itertools.combinations(nums, r):
                or_val = functools.reduce(lambda a, b: a | b, subset)
                if or_val == total_or:
                    count += 1
        return count