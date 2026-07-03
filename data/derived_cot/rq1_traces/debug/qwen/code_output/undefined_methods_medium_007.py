class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        n = len(nums)
        low = 0
        high = n - 1
        while low <= high:
            mid = (low + high) // 2
            is_peak = (mid == 0 or nums[mid] >= nums[mid-1]) and (mid == n-1 or nums[mid] >= nums[mid+1])
            if is_peak:
                return mid
            elif nums[mid] <= nums[mid+1]:
                low = mid + 1
            else:
                high = mid - 1
        return -1