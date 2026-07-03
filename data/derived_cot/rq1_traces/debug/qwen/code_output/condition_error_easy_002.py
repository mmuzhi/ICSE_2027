class Solution:
    def minimumOperations(self, nums: List[int]) -> int:
        operations = 0
        for num in nums:
            if num < 1:
                operations += (1 - num)
        return operations