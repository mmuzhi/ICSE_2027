class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        stack = []
        res = 0
        mod_arr = [float('-inf')] + arr + [float('-inf')]
        for i, num in enumerate(mod_arr):
            while stack and mod_arr[stack[-1]] > num:
                cur = stack.pop()
                if cur == 0 or cur == len(mod_arr) - 1:
                    continue
                left = stack[-1] if stack else -1
                res += mod_arr[cur] * (i - cur) * (cur - left)
            stack.append(i)
        return res % (10**9 + 7)