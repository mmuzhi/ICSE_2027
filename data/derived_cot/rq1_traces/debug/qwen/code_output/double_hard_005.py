class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [-1] * n
        first_greater = [-1] * n
        stack = []
        for i in range(n):
            while stack and nums[stack[-1]] < nums[i]:
                idx = stack.pop()
                first_greater[idx] = i
            stack.append(i)
        
        next_greater = [-1] * n
        stack = []
        for i in range(n-1, -1, -1):
            while stack and nums[stack[-1]] <= nums[i]:
                stack.pop()
            if stack:
                next_greater[i] = stack[-1]
            else:
                next_greater[i] = -1
            stack.append(i)
        
        for i in range(n):
            if first_greater[i] != -1 and next_greater[first_greater[i]] != -1:
                ans[i] = nums[next_greater[first_greater[i]]]
        return ans