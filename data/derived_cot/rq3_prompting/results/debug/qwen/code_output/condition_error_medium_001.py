class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        if n == 0:
            return True
        if n == 1:
            return True
        if n == 2:
            return nums[0] == nums[1]
        
        checks = (True, True, True)
        
        for curr, prev1, prev2 in zip(nums[2:], nums[1:], nums):
            new_state = (checks[1] and curr == prev1) or (checks[0] and 2 * prev1 == prev2 + curr)
            checks = (checks[1], checks[2], new_state)
        
        return checks[2]