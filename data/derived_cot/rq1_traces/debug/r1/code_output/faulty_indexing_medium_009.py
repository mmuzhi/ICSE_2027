class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        stack = []
        res = 0
        arr = [float('-inf')] + arr + [float('-inf')]
        for i, num in enumerate(arr):
            while stack and arr[stack[-1]] > num:
                cur = stack.pop()
                left_bound = stack[-1]
                right_bound = i
                res += arr[cur] * (cur - left_bound) * (right_bound - cur)
            stack.append(i)
        return res % (10**9 + 7)