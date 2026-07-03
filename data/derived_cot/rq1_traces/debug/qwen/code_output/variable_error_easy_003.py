class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        nums.sort()
        n = len(nums)
        if n - k == 0:
            return 0
        res = float('inf')
        for i in range(0, k + 1):
            diff = nums[i + n - k - 1] - nums[i]
            res = min(res, diff)
        return res