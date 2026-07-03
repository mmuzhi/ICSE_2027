class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        n = len(arr)
        left = [0] * n
        right = [0] * n
        stack = []
        for i in range(n):
            while stack and arr[stack[-1]] > arr[i]:
                stack.pop()
            left[i] = stack[-1] + 1 if stack else 0
            stack.append(i)
        
        stack = []
        for i in range(n-1, -1, -1):
            while stack and arr[stack[-1]] >= arr[i]:
                stack.pop()
            right[i] = stack[-1] if stack else n-1
            stack.append(i)
        
        ans = 0
        mod = 10**9 + 7
        for i in range(n):
            ans = (ans + arr[i] * (left[i] - i + right[i] - i + 1)) % mod
        return ans