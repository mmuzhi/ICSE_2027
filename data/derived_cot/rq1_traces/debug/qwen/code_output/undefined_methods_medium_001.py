class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [0] * n
        for i in range(n):
            for j in range(n):
                res[i] += abs(nums[i] - nums[j])
        return res