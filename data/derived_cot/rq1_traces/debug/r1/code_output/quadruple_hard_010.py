import bisect
from typing import List

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        window = []
        ans = []
        for i, x in enumerate(nums):
            bisect.insort(window, x)
            # Remove the element that's out of the window
            if len(window) > k:
                element_to_remove = nums[i - k]
                index = bisect.bisect_left(window, element_to_remove)
                if index < len(window) and window[index] == element_to_remove:
                    del window[index]
            # Check if the window is exactly size k
            if len(window) == k:
                if k % 2 == 1:
                    median = window[k // 2]
                else:
                    median = (window[k // 2 - 1] + window[k // 2]) / 2
                ans.append(median)
        return ans