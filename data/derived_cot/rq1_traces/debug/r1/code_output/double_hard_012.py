from sortedcontainers import SortedList
from typing import List

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        tree = SortedList()
        ans = []
        for i, x in enumerate(nums):
            tree.add(x)
            if len(tree) > k:
                tree.remove(nums[i - k])
            if len(tree) == k:
                if k % 2 == 1:
                    median = tree[k // 2]
                else:
                    median = (tree[k // 2 - 1] + tree[k // 2]) / 2
                ans.append(float(median))
        return ans