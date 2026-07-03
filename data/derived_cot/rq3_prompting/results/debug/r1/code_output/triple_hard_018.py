from typing import List
import heapq

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        # Two heaps: small (max-heap) and large (min-heap)
        small = []  # store negative values for max-heap behavior
        large = []
        # Lazy deletion map: element -> count of elements to be removed
        to_remove = {}
        
        # Helper function to balance the heaps
        def _balance():
            # Ensure small has exactly (k+1)//2 elements (or k//2+1 for odd k)
            while len(small) > len(large) + 1:
                heapq.heappush(large, -heapq.heappop(small))
            while len(large) > len(small):
                heapq.heappush(small, -heapq.heappop(large))
        
        # Helper to remove a specific element lazily
        def _lazy_remove(heap, val):
            # Actually we increment the to_remove count and pop invalid from top
            pass  # The removal is handled in the main loop
        
        ans = []
        for i, x in enumerate(nums):
            # Add new element to appropriate heap
            if not small or x <= -small[0]:
                heapq.heappush(small, -x)
            else:
                heapq.heappush(large, x)
            
            # Mark the element that slides out for removal
            if i >= k:
                out = nums[i - k]
                to_remove[out] = to_remove.get(out, 0) + 1
                # Remove the element that is out if it's at the top of a heap
                # We'll clean up after balancing
            
            # Balance heaps
            _balance()
            
            # Lazy clean: remove top elements that are marked for deletion
            while small and to_remove.get(-small[0], 0) > 0:
                val = -heapq.heappop(small)
                to_remove[val] -= 1
                if to_remove[val] == 0:
                    del to_remove[val]
            while large and to_remove.get(large[0], 0) > 0:
                val = heapq.heappop(large)
                to_remove[val] -= 1
                if to_remove[val] == 0:
                    del to_remove[val]
            
            # If window size is k, compute median
            if i >= k - 1:
                if k % 2 == 1:
                    ans.append(-small[0] * 1.0)
                else:
                    ans.append((-small[0] + large[0]) / 2.0)
        
        return ans