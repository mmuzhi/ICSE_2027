class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(arr)
        left_bound = [-1] * n
        right_bound = [n] * n
        stack = []
        
        # Compute left boundaries
        for i in range(n):
            while stack and arr[stack[-1]] > arr[i]:
                idx = stack.pop()
                left_bound[idx] = i
            stack.append(i)
        
        stack = []
        # Compute right boundaries
        for i in range(n-1, -1, -1):
            while stack and arr[stack[-1]] >= arr[i]:
                idx = stack.pop()
                right_bound[idx] = i
            stack.append(i)
        
        res = 0
        for i in range(n):
            res = (res + arr[i] * (i - left_bound[i]) * (right_bound[i] - i)) % MOD
        
        return res