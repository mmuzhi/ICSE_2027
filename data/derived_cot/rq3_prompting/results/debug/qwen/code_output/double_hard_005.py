class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [-1] * n
        nge1 = [-1] * n
        stack = []
        for i in range(n-1, -1, -1):
            while stack and nums[stack[-1]] <= nums[i]:
                stack.pop()
            if stack:
                nge1[i] = nums[stack[-1]]
            else:
                nge1[i] = -1
            stack.append(i)
        
        stack2 = []
        for i in range(n-1, -1, -1):
            if nge1[i] != -1:
                stack2.append((nge1[i], nums[i]))
            while stack2 and stack2[-1][0] <= nums[i]:
                stack2.pop()
            if stack2:
                ans[i] = stack2[-1][0]
            else:
                ans[i] = -1
        
        return ans