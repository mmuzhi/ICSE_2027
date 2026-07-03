class Solution:
    def numWays(self, s: str) -> int:
        MOD = 10**9 + 7
        ones = [i for i, c in enumerate(s) if c == '1']
        m = len(ones)
        if m == 0:
            n = len(s)
            return ((n - 1) * (n - 2) // 2) % MOD
        if m % 3 != 0:
            return 0
        split1 = m // 3
        split2 = 2 * split1
        return ((ones[split1] - ones[split1 - 1]) * (ones[split2] - ones[split2 - 1])) % MOD