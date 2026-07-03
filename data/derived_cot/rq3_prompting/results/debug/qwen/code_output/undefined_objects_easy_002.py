class Solution:
    def getMinDistance(self, nums, target, start) -> int:
        curVal = len(nums)
        start_index_forward = max(start, 0)
        for i in range(start_index_forward, len(nums)):
            if nums[i] == target:
                curVal = min(curVal, abs(i - start))
                break
        start_index_backward = min(start, len(nums) - 1)
        j = start_index_backward
        while j >= 0:
            if nums[j] == target:
                curVal = min(curVal, abs(j - start))
                break
            j -= 1
        return curVal