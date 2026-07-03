class Solution:
    def minBitFlips(self, start: int, goal: int) -> int:
        s = bin(start)[2:]
        g = bin(goal)[2:]
        n = max(len(s), len(g))
        s = s.zfill(n)
        g = g.zfill(n)
        count = 0
        for i in range(n):
            if s[i] != g[i]:
                count += 1
        return count