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
            found = False
            for c in range(self.c):
                if i == 0:
                    apples_in_col = self.pfsum_col[self.r-1][c]
                else:
                    apples_in_col = self.pfsum_col[self.r-1][c] - self.pfsum_col[i-1][c]
                if apples_in_col > 0:
                    found = True
                    break
            if found:
                return 1
            return 0
        
        @cache
        def getWays(i, j, k):
            if k == 1:
                found = False
                for c in range(j, self.c):
                    if i == 0:
                        apples_in_col = self.pfsum_col[self.r-1][c]
                    else:
                        apples_in_col = self.pfsum_col[self.r-1][c] - self.pfsum_col[i-1][c]
                    if apples_in_col > 0:
                        found = True
                        break
                if found:
                    return 1
                return 0
            else:
                t_cnt = 0
                # horizontally cut
                for nr in range(i, self.r):
                    if nr == self.r - 1:
                        continue
                    found = False
                    for c in range(j, self.c):
                        if i == 0:
                            apples_in_col = self.pfsum_col[nr][c]
                        else:
                            apples_in_col = self.pfsum_col[nr][c] - self.pfsum_col[i-1][c]
                        if apples_in_col > 0:
                            found = True
                            break
                    if found:
                        t_cnt += getWays(nr+1, j, k-1)
                
                # vertically cut
                for nc in range(j, self.c):
                    if nc == self.c - 1:
                        continue
                    found = False
                    for r in range(i, self.r):
                        if j == 0:
                            apples_in_row = self.pfsum_row[r][nc]
                        else:
                            apples_in_row = self.pfsum_row[r][nc] - self.pfsum_row[r][j-1]
                        if apples_in_row > 0:
                            found = True
                            break
                    if found:
                        t_cnt += getWays(i, nc+1, k-1)
                
                return t_cnt % (1000000007)
        
        return getWays(0, 0, k) % (1000000007)