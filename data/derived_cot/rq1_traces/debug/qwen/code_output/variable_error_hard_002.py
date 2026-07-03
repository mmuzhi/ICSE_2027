class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [-1] * n
        first = [-1] * n
        stack = []
        
        # First pass: find the first greater element to the right
        for i in range(n-1, -1, -1):
            while stack and nums[stack[-1]] <= nums[i]:
                stack.pop()
            if stack:
                first[i] = nums[stack[-1]]
            else:
                first[i] = -1
            stack.append(i)
        
        # Clear the stack for the second pass
        stack = []
        for i in range(n-1, -1, -1):
            if first[i] == -1:
                continue
            while stack and nums[stack[-1]] <= first[i]:
                stack.pop()
            if stack:
                ans[i] = nums[stack[-1]]
            else:
                ans[i] = -1
            stack.append(i)
        
        return ans