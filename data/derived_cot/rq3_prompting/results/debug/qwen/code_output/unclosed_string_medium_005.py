class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        n = len(arr)
        L = [-1] * n
        R = [n] * n
        
        stack = []
        for i in range(n):
            while stack and arr[stack[-1]] >= arr[i]:
                stack.pop()
            if stack:
                L[i] = stack[-1]
            else:
                L[i] = -1
            stack.append(i)
        
        stack = []
        for i in range(n-1, -1, -1):
            while stack and arr[stack[-1]] >= arr[i]:
                stack.pop()
            if stack:
                R[i] = stack[-1]
            else:
                R[i] = n
            stack.append(i)
        
        res = 0
        mod = 10**9 + 7
        for i in range(n):
            res = (res + arr[i] * (i - L[i]) * (R[i] - i)) % mod
        
        return res