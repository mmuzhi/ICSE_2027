class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        n = len(nums)
        if n < 2:
            return [-1] * n
        
        nge_index = [-1] * n
        stack = []
        for i in range(n):
            while stack and nums[stack[-1]] < nums[i]:
                j = stack.pop()
                nge_index[j] = i
            stack.append(i)
        
        ans = [-1] * n
        for i in range(n):
            if nge_index[i] != -1:
                if nge_index[nge_index[i]] != -1:
                    ans[i] = nums[nge_index[nge_index[i]]]
                else:
                    ans[i] = -1
            else:
                ans[i] = -1
        return ans