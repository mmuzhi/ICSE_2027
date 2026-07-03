class Solution:
    def findMaxK(self, nums: List[int]) -> int:
        s = set(nums)
        max_val = -1
        for x in nums:
            if x > 0:
                if -x in s:
                    return -1
                else:
                    if x > max_val:
                        max_val = x
        return max_val