class Solution:
    def longestWPI(self, A):
        curr, ans, D = 0, 0, {}
        for e, i in enumerate(map(lambda x: (-1, 1)[x > 0], A)):
            curr += i
            D[curr] = D.get(curr, e)
            if curr > 0:
                ans = max(ans, e + 1)
            else:
                if curr - 1 in D:
                    ans = max(ans, e - D[curr - 1])
        return ans