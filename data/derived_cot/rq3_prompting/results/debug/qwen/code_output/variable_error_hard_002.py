class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        first_greater_index = [-1] * n
        stack = []
        for i in range(n-1, -1, -1):
            while stack and nums[stack[-1]] <= nums[i]:
                stack.pop()
            if stack:
                first_greater_index[i] = stack[-1]
            else:
                first_greater_index[i] = -1
            stack.append(i)
        
        ans = [-1] * n
        for i in range(n):
            if first_greater_index[i] == -1:
                continue
            j = first_greater_index[i] + 1
            while j < n and nums[j] <= nums[i]:
                j += 1
            if j < n:
                ans[i] = nums[j]
            else:
                ans[i] = -1
        return ans