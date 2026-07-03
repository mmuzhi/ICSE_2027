from typing import List
import bisect

class Solution:
    def answerQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        nums.sort()
        prefix = [0]
        for num in nums:
            prefix.append(prefix[-1] + num)
        res = []
        for q in queries:
            # largest index i such that prefix[i] <= q
            i = bisect.bisect_right(prefix, q) - 1
            res.append(max(0, i))
        return res