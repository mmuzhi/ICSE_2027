class Solution:
    def sumSubarrayMins(self, arr: List[int]) -> int:
        n = len(arr)
        if n == 0:
            return 0
        stack = []
        res = 0
        mod = 10**9 + 7
        
        for i in range(n):
            while stack and arr[stack[-1]] > arr[i]:
                cur = stack.pop()
                if stack:
                    res += arr[cur] * (i - cur) * (cur - stack[-1])
                else:
                    res += arr[cur] * (i - cur) * (cur + 1)
            stack.append(i)
        
        return res % mod