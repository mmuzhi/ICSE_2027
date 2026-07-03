class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        n = len(arr)
        arr = [float('-inf')] + arr + [float('-inf')]
        res = 0
        stack = []
        for i in range(len(arr)):
            while stack and arr[stack[-1]] > arr[i]:
                cur = stack.pop()
                left_bound = stack[-1] if stack else -1
                res += arr[cur] * (cur - left_bound) * (i - cur)
            stack.append(i)
        return res % (10**9 + 7)