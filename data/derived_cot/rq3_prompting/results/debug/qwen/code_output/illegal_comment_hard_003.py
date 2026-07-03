class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [-1] * n
        stack = []
        second_stack = []
        
        for i in range(n):
            while second_stack and nums[second_stack[-1][0]] < nums[i] and second_stack[-1][1] < i:
                j = second_stack.pop()[0]
                ans[j] = nums[i]
            
            buff = []
            while stack and nums[stack[-1]] < nums[i]:
                k = stack.pop()
                buff.append((k, i))
            
            for (k, first_index) in buff:
                second_stack.append((k, first_index))
            
            stack.append(i)
        
        return ans