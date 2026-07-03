class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total = sum(nums)
        s1 = 0
        s2 = total
        arr = []
        for i in range(n):
            total_abs = 0
            for j in range(i+1, n):
                total_abs += abs(nums[i] - nums[j])
            arr.append(total_abs)
        return arr