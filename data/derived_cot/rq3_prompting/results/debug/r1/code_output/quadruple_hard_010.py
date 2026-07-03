from typing import List
import heapq

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        left = []   # max-heap (store negatives)
        right = []  # min-heap
        to_remove = {}
        ans = []

        def balance():
            # aim: size(left) == size(right) or size(left) == size(right) + 1
            while len(left) > len(right) + 1:
                neg_val = heapq.heappop(left)
                heapq.heappush(right, -neg_val)
            while len(right) > len(left):
                val = heapq.heappop(right)
                heapq.heappush(left, -val)

        def add(val):
            if not left or val <= -left[0]:
                heapq.heappush(left, -val)
            else:
                heapq.heappush(right, val)
            balance()

        def remove_val(val):
            # mark for lazy deletion
            to_remove[val] = to_remove.get(val, 0) + 1
            # clean heaps
            while left and to_remove.get(-left[0], 0) > 0:
                key = -left[0]
                to_remove[key] -= 1
                if to_remove[key] == 0:
                    del to_remove[key]
                heapq.heappop(left)
            while right and to_remove.get(right[0], 0) > 0:
                key = right[0]
                to_remove[key] -= 1
                if to_remove[key] == 0:
                    del to_remove[key]
                heapq.heappop(right)

        for i, x in enumerate(nums):
            add(x)
            if i >= k:
                remove_val(nums[i - k])
            if i >= k - 1:
                if k % 2 == 1:
                    ans.append(-left[0] * 1.0)
                else:
                    ans.append((-left[0] + right[0]) / 2.0)

        return ans