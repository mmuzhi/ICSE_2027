class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        n = len(nums)
        total = sum(nums)
        def dnc(l, r, base):
            if l >= r:
                return -1
            if l == r-1:
                if base == total - base - nums[l]:
                    return l
                return -1
            
            mid = (l + r) // 2
            left_ans = dnc(l, mid, base)
            if left_ans != -1:
                return left_ans
            
            left_sum_mid = base + sum(nums[l:mid])
            right_sum_mid = total - left_sum_mid - nums[mid]
            if left_sum_mid == right_sum_mid:
                return mid
            
            right_base = base + sum(nums[l:mid+1])
            right_ans = dnc(mid+1, r, right_base)
            return right_ans
        
        return dnc(0, n, 0)