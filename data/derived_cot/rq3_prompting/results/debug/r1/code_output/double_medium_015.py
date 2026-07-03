from typing import List

class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total = sum(nums)
        left_sum = 0
        res = []
        for i, num in enumerate(nums):
            right_sum = total - left_sum - num
            left_count = i
            right_count = n - i - 1
            left_diff = num * left_count - left_sum
            right_diff = right_sum - num * right_count
            res.append(left_diff + right_diff)
            left_sum += num
        return res