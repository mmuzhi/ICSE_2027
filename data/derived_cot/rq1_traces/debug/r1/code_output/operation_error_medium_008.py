class Solution:
    def longestWPI(self, A):
        curr, ans, D = 0, 0, {}
        for e, i in enumerate(map(lambda x: 1 if x > 8 else -1, A)):
            curr += i
            if curr not in D:
                D[curr] = e
            if curr > 0:
                ans = max(ans, e + 1)
            else:
                prev_index = D.get(curr - 1, e)
                ans = max(ans, e - prev_index)
        return ans