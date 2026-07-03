class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        n = len(edges)
        ans = -1
        for i in range(n):
            v = [0] * n
            t = 1
            c = i
            while c >= 0:
                if c >= n:
                    break
                if v[c] != 0:
                    if v[c][0] == i:
                        ans = max(ans, t - v[c][1])
                    break
                else:
                    v[c] = [i, t]
                    t += 1
                    c = edges[c]
        return ans