from typing import List

class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total = sum(nums)
        s1 = 0
        s2 = total
        arr = []
        for i in range(n):
            left = nums[i] * i - s1
            right = (s2 - nums[i]) - nums[i] * (n - i - 1)
            arr.append(left + right)
            s1 += nums[i]
            s2 = total - s1
        return arr