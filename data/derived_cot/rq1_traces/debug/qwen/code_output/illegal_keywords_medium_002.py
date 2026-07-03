class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        p1 = 0
        count = 1
        for p2 in range(1, len(nums)):
            if nums[p2] == nums[p1]:
                count += 1
                if count <= 2:
                    p1 += 1
                    nums[p1] = nums[p2]
            else:
                count = 1
                p1 += 1
                nums[p1] = nums[p2]
        return p1 + 1