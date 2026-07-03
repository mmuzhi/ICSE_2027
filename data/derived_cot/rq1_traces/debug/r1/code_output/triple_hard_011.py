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
        
        return self.getWays(0, 0, k - 1) % (1000000007)
    
    
    @lru_cache(maxsize=None)
    def getWays(self, i: int, j: int, k: int) -> int:
        if k == 0:
            found = False
            for c in range(j, self.c):
                apple_in_region = self.pfsum_col[self.r - 1][c]
                if i > 0:
                     apple_in_region -= self.pfsum_col[i - 1][c]
                if apple_in_region > 0:
                    found = True
                    break
            if found:
                return 1
            return 0
        else:
            t_cnt = 0
            # Check horizontal cuts
            nr = i
            while nr < self.r - 1:
                cannot_cut = True
                current_nr = nr
                while current_nr < self.r - 1 and cannot_cut:
                    apple_in_region = self.pfsum_row[current_nr][self.c - 1]
                    if j > 0:
                        apple_in_region -= self.pfsum_row[current_nr][j - 1]
                    if apple_in_region > 0:
                        cannot_cut = False
                    else:
                        current_nr += 1
                if current_nr < self.r - 1:
                    t_cnt += self.getWays(current_nr + 1, j, k - 1)
                    current_nr += 1  # Move past this cut to find other possibilities
                    # Check further cuts
                    while current_nr < self.r - 1:
                        apple_in_region = self.pfsum_row[current_nr][self.c - 1]
                        if j > 0:
                            apple_in_region -= self.pfsum_row[current_nr][j - 1]
                        if apple_in_region > 0:
                            t_cnt += self.getWays(current_nr + 1, j, k - 1)
                        current_nr += 1
                break  # Exit loop after processing all possible horizontal cuts from current nr
            
            # Check vertical cuts
            nc = j
            while nc < self.c - 1:
                cannot_cut = True
                current_nc = nc
                while current_nc < self.c - 1 and cannot_cut:
                    apple_in_region = self.pfsum_col[self.r - 1][current_nc]
                    if i > 0:
                        apple_in_region -= self.pfsum_col[i - 1][current_nc]
                    if apple_in_region > 0:
                        cannot_cut = False
                    else:
                        current_nc += 1
                if current_nc < self.c - 1:
                    t_cnt += self.getWays(i, current_nc + 1, k - 1)
                    current_nc += 1
                    # Check further cuts
                    while current_nc < self.c - 1:
                        apple_in_region = self.pfsum_col[self.r - 1][current_nc]
                        if i > 0:
                            apple_in_region -= self.pfsum_col[i - 1][current_nc]
                        if apple_in_region > 0:
                            t_cnt += self.getWays(i, current_nc + 1, k - 1)
                        current_nc += 1
                break  # Exit loop after processing all possible vertical cuts from current nc
            
            return t_cnt