from typing import List
from functools import lru_cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        MOD = 10**9 + 7
        r, c = len(pizza), len(pizza[0])
        # 2D prefix sum: pre[i+1][j+1] = number of apples in rectangle (0,0) to (i,j)
        pre = [[0] * (c + 1) for _ in range(r + 1)]
        for i in range(r):
            for j in range(c):
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j] - pre[i][j] + (1 if pizza[i][j] == 'A' else 0)

        # helper to count apples in subrectangle (i,j) to (r-1,c-1)
        def apples(i, j):
            return pre[r][c] - pre[i][c] - pre[r][j] + pre[i][j]

        total_apples = pre[r][c]
        if total_apples < k:
            return 0
        if k == 1:
            return 1

        @lru_cache(None)
        def dp(i, j, pieces):
            if pieces == 1:
                return 1 if apples(i, j) > 0 else 0
            ans = 0
            # horizontal cuts
            for x in range(i, r - 1):
                if apples(i, j) > 0 and apples(x + 1, j) > 0:
                    # top part has apples? Actually we only need top part to have apples.
                    # Check if top part (i..x, j..c-1) has at least one apple.
                    top_apples = pre[x + 1][c] - pre[i][c] - pre[x + 1][j] + pre[i][j]
                    if top_apples > 0:
                        ans = (ans + dp(x + 1, j, pieces - 1)) % MOD
            # vertical cuts
            for y in range(j, c - 1):
                # left part (i..r-1, j..y) has apples?
                left_apples = pre[r][y + 1] - pre[i][y + 1] - pre[r][j] + pre[i][j]
                if left_apples > 0:
                    ans = (ans + dp(i, y + 1, pieces - 1)) % MOD
            return ans

        return dp(0, 0, k) % MOD