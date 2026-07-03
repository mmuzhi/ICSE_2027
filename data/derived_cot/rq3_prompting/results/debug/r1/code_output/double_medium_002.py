from typing import List

class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return 0
        
        low, high = 0, n - 1
        while low <= high:
            mid = (low + high) // 2
            # Check if mid is a peak
            if (mid == 0 or nums[mid] >= nums[mid - 1]) and (mid == n - 1 or nums[mid] >= nums[mid + 1]):
                return mid
            # If right neighbor is greater, peak lies on the right
            elif mid < n - 1 and nums[mid] <= nums[mid + 1]:
                low = mid + 1
            else:
                high = mid - 1
        
        return -1  # Should never be reached as a peak always exists