from typing import List

class Solution:
    def calculateAbsoluteDifference(self, s1: int, num: int, i: int, s2: int, n: int) -> int:
        return num * i - s1 + (s2 - num) - num * (n - 1 - i)

    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total = sum(nums)
        s1 = 0
        s2 = total
        arr = []
        for i in range(n):
            arr.append(self.calculateAbsoluteDifference(s1, nums[i], i, s2, n))
            s1 = s1 + nums[i]
            s2 = total - s1

        return arr