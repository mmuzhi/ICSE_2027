class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        stack = []
        res = 0
        n = len(arr)
        
        for i, num in enumerate(arr):
            while stack and arr[stack[-1]] > num:
                cur = stack.pop()
                left_bound = stack[-1] if stack else -1
                res += arr[cur] * (cur - left_bound) * (i - cur)
            stack.append(i)
        
        while stack:
            cur = stack.pop()
            left_bound = stack[-1] if stack else -1
            res += arr[cur] * (cur - left_bound) * (n - cur)
        
        return res % (10**9 + 7)