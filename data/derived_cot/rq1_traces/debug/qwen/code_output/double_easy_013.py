class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        def dnc(l, r, lo, hi):
            if l == r - 1:
                return l if lo == hi else -1
            
            mid = (l + r) // 2
            left_seg = sum(nums[l:mid])
            right_seg = sum(nums[mid:r])
            
            left_index = dnc(l, mid, lo, hi + right_seg)
            if left_index != -1:
                return left_index
                
            right_index = dnc(mid, r, lo + left_seg, hi)
            return right_index
        
        return dnc(0, len(nums), 0, 0)