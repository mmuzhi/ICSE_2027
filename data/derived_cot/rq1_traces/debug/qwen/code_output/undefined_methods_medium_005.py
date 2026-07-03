class Solution:
    def longestWPI(self, A):
        curr, ans, min_prefix_index = 0, 0, {}
        for i in range(len(A)):
            curr += A[i]
            if curr not in min_prefix_index:
                min_prefix_index[curr] = i
            if curr > 0:
                ans = max(ans, i+1 - min_prefix_index.get(0, -1))
            else:
                if curr not in min_prefix_index:
                    min_prefix_index[curr] = i
                if min_prefix_index.get(curr-1) is not None:
                    ans = max(ans, i+1 - min_prefix_index[curr-1])
        return ans