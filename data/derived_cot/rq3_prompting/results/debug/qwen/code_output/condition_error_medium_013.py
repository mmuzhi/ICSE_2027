class Solution:
    def minPairSum(self, nums: List[int]) -> int:
        nums.sort()
        left = 0
        right = len(nums) - 1
        list2 = []
        while left < right:
            list2.append(nums[left] + nums[right])
            left += 1
            right -= 1
        return max(list2)