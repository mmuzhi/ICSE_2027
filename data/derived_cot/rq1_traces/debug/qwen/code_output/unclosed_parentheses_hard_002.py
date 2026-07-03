import heapq
from collections import defaultdict

class MedianFinder:
    def __init__(self):
        self.left = []   # Max-heap (store negative values)
        self.right = []  # Min-heap
        self.to_remove = defaultdict(int)

    def addNum(self, num):
        if not self.left or num <= -self.left[0]:
            heapq.heappush(self.left, -num)
        else:
            heapq.heappush(self.right, num)
        self._balance()

    def removeNum(self, num):
        self.to_remove[num] += 1

    def findMedian(self):
        while self.left and self.to_remove.get(-self.left[0], 0) > 0:
            x = -self.left[0]
            self.to_remove[x] -= 1
            heapq.heappop(self.left)
        while self.right and self.to_remove.get(self.right[0], 0) > 0:
            x = self.right[0]
            self.to_remove[x] -= 1
            heapq.heappop(self.right)
        
        if len(self.left) == len(self.right):
            return (-self.left[0] + self.right[0]) / 2
        else:
            return -self.left[0]

    def _balance(self):
        if len(self.left) < len(self.right):
            x = heapq.heappop(self.right)
            heapq.heappush(self.left, -x)
        if len(self.left) > len(self.right) + 1:
            x = heapq.heappop(self.left)
            heapq.heappush(self.right, -x)

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        mf = MedianFinder()
        ans = []
        for i, x in enumerate(nums):
            if i >= k - 1:
                mf.removeNum(nums[i - k + 1])
            mf.addNum(x)
            if i >= k - 1:
                ans.append(mf.findMedian())
        return ans