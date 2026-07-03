class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        n = len(arr)
        mod = 10**9 + 7
        left_bound = [-1] * n
        stack = []
        for i in range(n):
            while stack and arr[stack[-1]] > arr[i]:
                stack.pop()
            left_bound[i] = stack[-1] if stack else -1
            stack.append(i)
        
        stack = []
        right_bound = [n] * n
        for i in range(n-1, -1, -1):
            while stack and arr[stack[-1]] > arr[i]:
                stack.pop()
            right_bound[i] = stack[-1] if stack else n
            stack.append(i)
        
        res = 0
        for i in range(n):
            left_span = i - left_bound[i]
            right_span = right_bound[i] - i
            res = (res + arr[i] * left_span * right_span) % mod
        return res