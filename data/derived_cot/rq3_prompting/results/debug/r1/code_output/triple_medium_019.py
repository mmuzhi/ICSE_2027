from typing import List

class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        arr = arr + [0]  # sentinel to pop all remaining elements
        stack = []
        res = 0
        
        for i, num in enumerate(arr):
            while stack and arr[stack[-1]] > num:
                cur = stack.pop()
                left = stack[-1] if stack else -1
                res += arr[cur] * (cur - left) * (i - cur)
            stack.append(i)
        
        return res % (10**9 + 7)