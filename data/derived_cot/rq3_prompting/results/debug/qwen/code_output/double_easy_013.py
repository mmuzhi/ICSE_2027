class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        def dnc(l, r):
            if l == r - 1:
                return l if sum(nums[l:r]) == 0 else -1
            mid = (l + r) // 2
            left_sum = sum(nums[l:mid])
            right_sum = sum(nums[mid:r])
            if left_sum == right_sum:
                return mid
            left_ind = dnc(l, mid)
            if left_ind != -1:
                return left_ind
            return dnc(mid, r)
        return dnc(0, len(nums))