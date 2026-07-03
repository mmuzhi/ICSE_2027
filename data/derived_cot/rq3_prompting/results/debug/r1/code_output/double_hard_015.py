from typing import List
from functools import lru_cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 10**9 + 7
        R = len(pizza)
        C = len(pizza[0])

        # 2D prefix sum of apples (1-indexed)
        pref = [[0] * (C + 1) for _ in range(R + 1)]
        for i in range(1, R + 1):
            row = pizza[i - 1]
            for j in range(1, C + 1):
                pref[i][j] = (
                    pref[i - 1][j]
                    + pref[i][j - 1]
                    - pref[i - 1][j - 1]
                    + (1 if row[j - 1] == 'A' else 0)
                )

        # Check if a sub-rectangle (r1,c1) to (r2,c2) inclusive has at least one apple
        def has_apple(r1: int, c1: int, r2: int, c2: int) -> bool:
            if r1 > r2 or c1 > c2:
                return False
            total = (
                pref[r2 + 1][c2 + 1]
                - pref[r1][c2 + 1]
                - pref[r2 + 1][c1]
                + pref[r1][c1]
            )
            return total > 0

        total_apples = pref[R][C]
        if total_apples < k:
            return 0

        @lru_cache(None)
        def dp(i: int, j: int, pieces: int) -> int:
            if pieces == 1:
                return 1 if has_apple(i, j, R - 1, C - 1) else 0

            ans = 0
            # Horizontal cuts: cut after row 'cut' (top piece rows i..cut)
            for cut in range(i, R - 1):
                if has_apple(i, j, cut, C - 1):
                    ans = (ans + dp(cut + 1, j, pieces - 1)) % MOD

            # Vertical cuts: cut after column 'cut' (left piece cols j..cut)
            for cut in range(j, C - 1):
                if has_apple(i, j, R - 1, cut):
                    ans = (ans + dp(i, cut + 1, pieces - 1)) % MOD

            return ans

        return dp(0, 0, k) % MOD