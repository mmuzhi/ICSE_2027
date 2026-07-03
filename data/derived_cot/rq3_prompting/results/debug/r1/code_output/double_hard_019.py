from collections import defaultdict

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        mem = defaultdict(int)
        MOD = 10**9 + 7

        def dfs(i: int, val: int = 0) -> int:
            if i == len(s):
                return 1
            if (i, val) in mem:
                return mem[(i, val)]

            total = 0
            if s[i] == "D":
                for nxt in range(0, val + 1):
                    total += dfs(i + 1, nxt) % MOD
            else:  # 'I'
                for nxt in range(val + 1, i + 2):
                    total += dfs(i + 1, nxt) % MOD

            total %= MOD
            mem[(i, val)] = total
            return total

        return dfs(0)