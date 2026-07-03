import bisect
from typing import List

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        window = []
        ans = []
        for i in range(len(nums)):
            bisect.insort(window, nums[i])
            if len(window) > k:
                # Remove the element that's out of the window
                index = bisect.bisect_left(window, nums[i - k])
                window.pop(index)
            if len(window) == k:
                if k % 2 == 1:
                    median = window[k // 2]
                else:
                    median = (window[k // 2 - 1] + window[k // 2]) / 2
                ans.append(median)
        return ans