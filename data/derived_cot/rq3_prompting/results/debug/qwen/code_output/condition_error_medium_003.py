class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        count_map = {}
        for num in nums:
            count_map[num] = count_map.get(num, 0) + 1
        
        new_length = 0
        for num in count_map:
            for _ in range(min(count_map[num], 2)):
                if new_length < len(nums):
                    nums[new_length] = num
                    new_length += 1
        return new_length