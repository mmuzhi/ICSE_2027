import heapq

class Solution:
    def secondGreaterElement(self, nums):
        ans = [-1] * len(nums)
        s = []
        wait = []
        for i, x in enumerate(nums):
            while wait and wait[0][0] < x:
                _, j = heapq.heappop(wait)
                ans[j] = x
            buff = []
            while s and nums[s[-1]] < x:
                j = s.pop()
                heapq.heappush(wait, (nums[j], j))
            s.append(i)
        return ans