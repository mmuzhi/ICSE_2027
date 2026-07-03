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
        
        if tot_apples < k + 1:
            return 0
        
        return self.getWays(0, 0, k) % (1000000007)
    
    @cache
    def getWays(self, i, j, k):
        total_apples = 0
        for r_idx in range(i, self.r):
            if j > 0:
                total_apples += self.pfsum_row[r_idx][self.c-1] - self.pfsum_row[r_idx][j-1]
            else:
                total_apples += self.pfsum_row[r_idx][self.c-1]
        
        if k == 1:
            if total_apples < 2:
                return 0
            found = False
            for nr in range(i+1, self.r):
                top_apples = 0
                for r_idx in range(i, nr):
                    if j > 0:
                        top_apples += self.pfsum_row[r_idx][self.c-1] - self.pfsum_row[r_idx][j-1]
                    else:
                        top_apples += self.pfsum_row[r_idx][self.c-1]
                bottom_apples = total_apples - top_apples
                if top_apples > 0 and bottom_apples > 0:
                    found = True
                    break
            
            if found:
                return 1
            
            found = False
            for nc in range(j+1, self.c):
                left_apples = 0
                for r_idx in range(i, self.r):
                    if j > 0:
                        left_apples += self.pfsum_row[r_idx][nc-1] - self.pfsum_row[r_idx][j-1]
                    else:
                        left_apples += self.pfsum_row[r_idx][nc-1]
                right_apples = total_apples - left_apples
                if left_apples > 0 and right_apples > 0:
                    found = True
                    break
            
            if found:
                return 1
            
            return 0
        else:
            cannot_cut = True
            nr = i
            t_cnt = 0
            while nr < self.r - 1:
                while nr < self.r - 1 and cannot_cut:
                    top_apples = 0
                    for r_idx in range(i, nr+1):
                        if j > 0:
                            top_apples += self.pfsum_row[r_idx][self.c-1] - self.pfsum_row[r_idx][j-1]
                        else:
                            top_apples += self.pfsum_row[r_idx][self.c-1]
                    bottom_apples = total_apples - top_apples
                    if bottom_apples == 0 or top_apples == 0:
                        nr += 1
                        continue
                    cannot_cut = False
                
                if not cannot_cut and nr < self.r - 1:
                    t_cnt += self.getWays(nr + 1, j, k - 1)
                
                nr += 1
            
            cannot_cut = True
            nc = j
            while nc < self.c - 1:
                while nc < self.c - 1 and cannot_cut:
                    left_apples = 0
                    for r_idx in range(i, self.r):
                        if j > 0:
                            left_apples += self.pfsum_row[r_idx][nc] - self.pfsum_row[r_idx][j-1]
                        else:
                            left_apples += self.pfsum_row[r_idx][nc]
                    right_apples = total_apples - left_apples
                    if right_apples == 0 or left_apples == 0:
                        nc += 1
                        continue
                    cannot_cut = False
                
                if not cannot_cut and nc < self.c - 1:
                    t_cnt += self.getWays(i, nc + 1, k - 1)
                
                nc += 1
            
            return t_cnt % (1000000007)