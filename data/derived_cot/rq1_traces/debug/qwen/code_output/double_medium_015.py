class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        total = sum(nums)
        if n == 0:
            return []
        prefix = [0] * n
        for i in range(1, n):
            prefix[i] = prefix[i-1] + nums[i-1]
        
        result = []
        for i in range(n):
            left_abs = nums[i] * i - prefix[i]
            if i < n-1:
                right_sum = total - prefix[i] - nums[i]
                right_count = n - i - 1
                right_abs = right_sum - nums[i] * right_count
            else:
                right_abs = 0
            result.append(left_abs + right_abs)
        return result