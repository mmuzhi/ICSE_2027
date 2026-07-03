from sortedcontainers import SortedList
from typing import List

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        sl = SortedList()
        ans = []
        for i, x in enumerate(nums):
            sl.add(x)
            if len(sl) > k:
                sl.remove(nums[i - k])
            if len(sl) == k:
                if k % 2 == 1:
                    ans.append(float(sl[k // 2]))
                else:
                    ans.append((sl[k // 2 - 1] + sl[k // 2]) / 2)
        return ans