import bisect

class Solution:
    def getSumAbsoluteDifferences(self, nums: List[int]) -> List[int]:
        n = len(nums)
        sorted_nums = sorted(nums)
        total = sum(nums)
        prefix = [0] * n
        prefix[0] = sorted_nums[0]
        for i in range(1, n):
            prefix[i] = prefix[i-1] + sorted_nums[i]
        
        ans = [0] * n
        for i in range(n):
            x = nums[i]
            left_count = bisect.bisect_right(sorted_nums, x)
            left_sum = prefix[left_count-1] if left_count > 0 else 0
            right_count = n - left_count
            right_sum = total - left_sum
            ans[i] = left_count * x - left_sum + right_sum - right_count * x
        return ans