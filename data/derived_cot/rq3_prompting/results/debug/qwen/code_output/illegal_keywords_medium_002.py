class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2:
            return n
        i = 1
        count = 1
        for j in range(1, n):
            if nums[j] == nums[i-1] and count < 2:
                nums[i] = nums[j]
                i += 1
                count += 1
            elif nums[j] == nums[i-1] and count == 2:
                continue
            else:
                nums[i] = nums[j]
                i += 1
                count = 1
        return i