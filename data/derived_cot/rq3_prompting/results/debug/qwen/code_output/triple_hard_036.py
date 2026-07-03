from collections import defaultdict

class Solution:
    def numPermsDISequence(self, s: str) -> int:
        mod = 10**9 + 7
        n = len(s)
        total = n + 1
        
        dp = defaultdict(lambda: defaultdict(int))
        for j in range(total):
            mask = 1 << j
            dp[mask][j] = 1
        
        for i in range(len(s)):
            new_dp = defaultdict(lambda: defaultdict(int))
            for mask, last_dict in dp.items():
                for last, count in last_dict.items():
                    if s[i] == 'I':
                        for j in range(last + 1, total):
                            if mask & (1 << j):
                                continue
                            new_mask = mask | (1 << j)
                            new_dp[new_mask][j] = (new_dp[new_mask].get(j, 0) + count) % mod
                    else:
                        for j in range(0, last):
                            if mask & (1 << j):
                                continue
                            new_mask = mask | (1 << j)
                            new_dp[new_mask][j] = (new_dp[new_mask].get(j, 0) + count) % mod
            dp = new_dp
        
        result = 0
        for last_dict in dp.values():
            result = (result + sum(last_dict.values())) % mod
        return result