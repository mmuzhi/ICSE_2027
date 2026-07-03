class Solution:
    def secondGreaterElement(self, nums):
        ans = [-1] * len(nums)
        s, ss = [], []
        for i, x in enumerate(nums):
            while ss and nums[ss[-1]] < x:
                ans[ss.pop()] = x
            buff = []
            while s and nums[s[-1]] < x:
                buff.append(s.pop())
            ss.extend(buff)
            s.append(i)
        return ans