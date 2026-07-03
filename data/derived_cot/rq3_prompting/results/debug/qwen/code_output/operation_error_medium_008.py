class Solution:
    def longestWPI(self, A):
        curr = 0
        min_prefix = 0
        min_index = 0
        ans = 0
        for e in range(len(A)):
            if A[e] == 8:
                curr += 1
            else:
                curr -= 1
            if curr < min_prefix:
                min_prefix = curr
                min_index = e + 1
            if curr > min_prefix:
                ans = max(ans, (e + 1) - min_index)
        return ans