from typing import List
from functools import cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        
        tot_apples = 0
        self.pfsum_row = []
        self.pfsum_col = []
        
        for i in range(self.r):
            pfr = 0
            pfs_r = [0] * self.c
            pfs_c = [0] * self.c
            for j in range(self.c):
                if i > 0:
                    pfs_c[j] += self.pfsum_col[i - 1][j]
                if pizza[i][j] == 'A':
                    pfr += 1
                    pfs_c[j] += 1
                    tot_apples += 1
                pfs_r[j] = pfr
            self.pfsum_row.append(pfs_r)
            self.pfsum_col.append(pfs_c)
        
        if tot_apples < k:
            return 0
        
        if k == 1:
            return 1
        
        return self.getWays(0, 0, k) % 1000000007
    
    
    @cache
    def getWays(self, i: int, j: int, k: int) -> int:
        MOD = 1000000007
        
        if k == 1:
            # Check if the whole remaining region has at least one apple
            for c in range(j, self.c):
                apples = self.pfsum_col[self.r - 1][c]
                if i > 0:
                    apples -= self.pfsum_col[i - 1][c]
                if apples > 0:
                    return 1
            return 0
        
        ans = 0
        
        # Horizontal cuts
        for nr in range(i, self.r - 1):
            has_apple = False
            for row in range(i, nr + 1):
                apples_in_row = self.pfsum_row[row][self.c - 1]
                if j > 0:
                    apples_in_row -= self.pfsum_row[row][j - 1]
                if apples_in_row > 0:
                    has_apple = True
                    break
            if has_apple:
                ans = (ans + self.getWays(nr + 1, j, k - 1)) % MOD
        
        # Vertical cuts
        for nc in range(j, self.c - 1):
            has_apple = False
            for col in range(j, nc + 1):
                apples_in_col = self.pfsum_col[self.r - 1][col]
                if i > 0:
                    apples_in_col -= self.pfsum_col[i - 1][col]
                if apples_in_col > 0:
                    has_apple = True
                    break
            if has_apple:
                ans = (ans + self.getWays(i, nc + 1, k - 1)) % MOD
        
        return ans