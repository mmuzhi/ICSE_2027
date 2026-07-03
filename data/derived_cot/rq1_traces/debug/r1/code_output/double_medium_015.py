from typing import List

class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total = sum(nums)
        s1 = 0
        s2 = total
        arr = []
        for i in range(n):
            left_diff = nums[i] * i - s1
            right_diff = s2 - nums[i] * (n - i)
            total_diff = left_diff + right_diff
            arr.append(total_diff)
            s1 += nums[i]
            s2 = total - s1
        return arr