from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        stack = [-1]
        res = 0
        MOD = 10**9 + 7
        
        for i, num in enumerate(arr):
            while len(stack) > 1 and arr[stack[-1]] > num:
                cur = stack.pop()
                res = (res + arr[cur] * (i - cur) * (cur - stack[-1])) % MOD
            stack.append(i)
            
        while len(stack) > 1:
            cur = stack.pop()
            res = (res + arr[cur] * (len(arr) - cur) * (cur - stack[-1])) % MOD
            
        return res