class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        nums.sort()
        l, r = 0, k
        res = float("inf")
        while r <= len(nums):
            res = min(res, nums[r-1] - nums[l])
            r += 1
            l += 1
        return res