class Solution:
    def minBitFlips(self, start: int, goal: int) -> int:
        def to_twos_complement(x):
            if x < 0:
                x += (1 << 50)
            return x
        
        start = to_twos_complement(start)
        goal = to_twos_complement(goal)
        
        s = bin(start)[2:].zfill(50)
        g = bin(goal)[2:].zfill(50)
        count = 0
        for i in range(50):
            if s[i] != g[i]:
                count += 1
        return count