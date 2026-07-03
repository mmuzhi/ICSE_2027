from typing import List
from functools import cache

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        MOD = 1000000007
        
        # Step 1, pre-process the apple array and get the 2D suffix sum
        self.apples = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(self.r - 1, -1, -1):
            for j in range(self.c - 1, -1, -1):
                self.apples[i][j] = self.apples[i+1][j] + self.apples[i][j+1] - self.apples[i+1][j+1] + (1 if pizza[i][j] == 'A' else 0)
        
        if self.apples[0][0] < k:
            return 0
        
        return self.getWays(0, 0, k) % MOD
    
    
    @cache
    def getWays(self, i, j, k):
        MOD = 1000000007
        if k == 1:
            # if only left one piece for cutting, we just need to check if there is any apple in the region
            if self.apples[i][j] > 0:
                return 1
            return 0
        else:
            t_cnt = 0
            # horizontally cut
            cannot_cut = True
            nr = i
            while nr < self.r - 1:
                # find the first row that we can start cutting
                while nr < self.r - 1 and cannot_cut:
                    if self.apples[i][j] - self.apples[nr + 1][j] > 0:
                        cannot_cut = False
                    else:
                        nr += 1
                        
                if nr < self.r - 1:
                    t_cnt = (t_cnt + self.getWays(nr + 1, j, k - 1)) % MOD
                nr += 1
                
            # vertically cut
            cannot_cut = True
            nc = j
            while nc < self.c - 1:
                # find the first col that we can start cutting
                while nc < self.c - 1 and cannot_cut:
                    if self.apples[i][j] - self.apples[i][nc + 1] > 0:
                        cannot_cut = False
                    else:
                        nc += 1
                
                if nc < self.c - 1:
                    t_cnt = (t_cnt + self.getWays(i, nc + 1, k - 1)) % MOD
                nc += 1
            
            return t_cnt