class Solution:
    def longestWPI(self, A):
        curr, ans, D = 0, 0, {}
        for e, h in enumerate(A):
            i = 1 if h > 8 else -1
            curr += i
            D[curr] = D.get(curr, e)
            ans = e + 1 if curr > 0 else max(ans, e - D.get(curr - 1, e))
        return ans