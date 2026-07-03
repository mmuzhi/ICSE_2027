from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        stack = []
        res = 0
        MOD = 10**9 + 7
        n = len(arr)
        
        for i, num in enumerate(arr):
            while stack and arr[stack[-1]] > num:
                cur = stack.pop()
                left = stack[-1] if stack else -1
                res += arr[cur] * (i - cur) * (cur - left)
            stack.append(i)
        
        # Process remaining elements (no smaller element to the right)
        while stack:
            cur = stack.pop()
            left = stack[-1] if stack else -1
            res += arr[cur] * (n - cur) * (cur - left)
        
        return res % MOD