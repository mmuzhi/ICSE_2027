from typing import List

class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total = sum(nums)
        s1 = 0
        s2 = total
        arr = []
        for i in range(n):
            s2 -= nums[i]
            arr.append(nums[i] * i - s1 + s2 - nums[i] * (n - 1 - i))
            s1 += nums[i]
        return arr