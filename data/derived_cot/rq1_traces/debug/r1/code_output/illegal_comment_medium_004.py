class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        mod = 10**9 + 7
        stack = []
        res = 0
        n = len(arr)
        
        for i in range(n):
            while stack and arr[stack[-1]] > arr[i]:
                cur = stack.pop()
                left_bound = stack[-1] if stack else -1
                right_bound = i
                res = (res + arr[cur] * (cur - left_bound) * (right_bound - cur)) % mod
            stack.append(i)
        
        while stack:
            cur = stack.pop()
            left_bound = stack[-1] if stack else -1
            right_bound = n
            res = (res + arr[cur] * (cur - left_bound) * (right_bound - cur)) % mod
        
        return res