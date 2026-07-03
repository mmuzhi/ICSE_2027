from typing import List

class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        def dnc(l, r, lo, hi):
            if l == r - 1:
                return l if lo == hi else -1
            
            mid = (l + r) // 2
            right_sum = sum(nums[mid:r])
            left_sum = sum(nums[l:mid])

            left_ind = dnc(l, mid, lo, hi + right_sum)
            return left_ind if left_ind != -1 else dnc(mid, r, lo + left_sum, hi)
        
        return dnc(0, len(nums), 0, 0)