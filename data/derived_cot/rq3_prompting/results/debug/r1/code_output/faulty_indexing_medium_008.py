from typing import List

class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        n = len(nums)
        low, high = 0, n - 1
        if n == 1:
            return 0
        while low <= high:
            mid = (low + high) // 2
            # Check if mid is a peak (strictly greater than neighbors)
            if (mid == 0 or nums[mid] > nums[mid - 1]) and (mid == n - 1 or nums[mid] > nums[mid + 1]):
                return mid
            # Move towards the greater neighbor (if right neighbor exists and is greater)
            if mid < n - 1 and nums[mid] < nums[mid + 1]:
                low = mid + 1
            else:
                high = mid - 1
        return -1