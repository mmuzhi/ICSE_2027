from typing import List

class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        ans = [-1] * len(nums)
        s, ss = [], []  # s: waiting for first greater, ss: waiting for second greater
        for i, x in enumerate(nums):
            while ss and nums[ss[-1]] < x:
                ans[ss.pop()] = x
            temp = []
            while s and nums[s[-1]] < x:
                temp.append(s.pop())
            while temp:
                ss.append(temp.pop())
            s.append(i)
        return ans