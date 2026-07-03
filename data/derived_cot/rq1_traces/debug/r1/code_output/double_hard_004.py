from typing import List
from functools import lru_cache

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
        
        return self.getWays(0, 0, k) % (10**9 + 7)
    
    
    @lru_cache(maxsize=None)
    def getWays(self, i, j, k):
        if k == 1:
            for c in range(j, self.c):
                apple_in_region = self.pfsum_col[self.r - 1][c]
                if i > 0:
                    apple_in_region -= self.pfsum_col[i - 1][c]
                if apple_in_region > 0:
                    return 1
            return 0
        else:
            t_cnt = 0
            # Check all possible horizontal cuts
            for nr in range(i, self.r - 1):
                has_apple = False
                for col in range(j, self.c):
                    sum_col = self.pfsum_col[nr][col]
                    if i > 0:
                        sum_col -= self.pfsum_col[i-1][col]
                    if sum_col > 0:
                        has_apple = True
                        break
                if has_apple:
                    t_cnt += self.getWays(nr + 1, j, k - 1)
            
            # Check all possible vertical cuts
            for nc in range(j, self.c - 1):
                has_apple = False
                for row in range(i, self.r):
                    sum_row = self.pfsum_row[row][nc]
                    if j > 0:
                        sum_row -= self.pfsum_row[row][j-1]
                    if sum_row > 0:
                        has_apple = True
                        break
                if has_apple:
                    t_cnt += self.getWays(i, nc + 1, k - 1)
            
            return t_cnt