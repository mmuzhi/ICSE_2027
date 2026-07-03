class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        n = len(arr)
        left_bound = [-1] * n
        right_bound = [n] * n
        
        stack = []
        for i in range(n):
            while stack and arr[stack[-1]] > arr[i]:
                stack.pop()
            if stack:
                left_bound[i] = stack[-1]
            else:
                left_bound[i] = -1
            stack.append(i)
        
        stack = []
        for i in range(n-1, -1, -1):
            while stack and arr[stack[-1]] > arr[i]:
                stack.pop()
            if stack:
                right_bound[i] = stack[-1]
            else:
                right_bound[i] = n
            stack.append(i)
        
        mod = 10**9 + 7
        res = 0
        for i in range(n):
            count_left = i - left_bound[i]
            count_right = right_bound[i] - i
            res = (res + arr[i] * count_left * count_right) % mod
        
        return res