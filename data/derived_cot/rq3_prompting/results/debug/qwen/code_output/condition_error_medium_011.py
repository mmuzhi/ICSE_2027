class Solution:
    def numWays(self, s: str) -> int:
        MOD = 10**9 + 7
        N = len(s)
        c1 = s.count('1')
        if c1 == 0:
            return ((N-1)*(N-2)//2) % MOD
        if c1 % 3 != 0:
            return 0
        c = c1 // 3
        ones = []
        for i, char in enumerate(s):
            if char == '1':
                ones.append(i)
        a = ones[c-1]
        b = ones[c]
        d = ones[2*c]
        e = ones[2*c+1]
        return (b - a) * (e - d) % MOD