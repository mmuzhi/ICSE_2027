class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        if len(nums) == 1:
            return 1
        ans = 2
        for i in range(2, len(nums)):
            if nums[i] == nums[ans-1] and nums[i] == nums[ans-2]:
                continue
            else:
                nums[ans] = nums[i]
                ans += 1
        return ans