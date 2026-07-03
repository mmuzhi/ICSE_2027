from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        stack = []
        res = 0
        n = len(arr)
        
        for i, num in enumerate(arr):
            while stack and arr[stack[-1]] > num:
                cur = stack.pop()
                left = cur - stack[-1] if stack else cur + 1
                res += arr[cur] * (i - cur) * left
            stack.append(i)
            
        while stack:
            cur = stack.pop()
            left = cur - stack[-1] if stack else cur + 1
            res += arr[cur] * (n - cur) * left
            
        return res % (10**9 + 7)