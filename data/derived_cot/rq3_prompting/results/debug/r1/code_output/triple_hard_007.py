from itertools import accumulate

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        MOD = 10**9 + 7
        dp = [1] * (len(s) + 1)
        for ch in s:
            if ch == 'I':
                dp = [x % MOD for x in accumulate(dp[:-1])]
            else:
                dp = [x % MOD for x in accumulate(dp[1:][::-1])][::-1]
        return sum(dp) % MOD