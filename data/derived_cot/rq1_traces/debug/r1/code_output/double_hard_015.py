from typing import List

class Solution:
    def ways(self, pizza: List[str], k: int) -> int:
        self.r = len(pizza)
        self.c = len(pizza[0])
        self.memo = {}
        
        # Compute 2D prefix sum array
        self.prefix = [[0] * (self.c + 1) for _ in range(self.r + 1)]
        for i in range(self.r):
            row_sum = 0
            for j in range(self.c):
                if pizza[i][j] == 'A':
                    row_sum += 1
                self.prefix[i + 1][j + 1] = self.prefix[i][j + 1] + row_sum
        
        total_apples = self.prefix[self.r][self.c]
        if total_apples < k:
            return 0
        if k == 1:
            return 1
        
        return self.getWays(0, 0, k) % (10**9 + 7)
    
    def getWays(self, i: int, j: int, k: int) -> int:
        key = (i, j, k)
        if key in self.memo:
            return self.memo[key]
        
        if k == 1:
            a, b = i, j
            c, d = self.r, self.c
            total = self.prefix[c][d] - self.prefix[a][d] - self.prefix[c][b] + self.prefix[a][b]
            res = 1 if total > 0 else 0
            self.memo[key] = res
            return res
        
        count = 0
        
        # Horizontal cuts
        for nr in range(i, self.r - 1):
            a_upper, b_upper = i, j
            c_upper, d_upper = nr + 1, self.c
            sum_upper = self.prefix[c_upper][d_upper] - self.prefix[a_upper][d_upper] - self.prefix[c_upper][b_upper] + self.prefix[a_upper][b_upper]
            if sum_upper > 0:
                count += self.getWays(nr + 1, j, k - 1)
        
        # Vertical cuts
        for nc in range(j, self.c - 1):
            a_left, b_left = i, j
            c_left, d_left = self.r, nc + 1
            sum_left = self.prefix[c_left][d_left] - self.prefix[a_left][d_left] - self.prefix[c_left][b_left] + self.prefix[a_left][b_left]
            if sum_left > 0:
                count += self.getWays(i, nc + 1, k - 1)
        
        self.memo[key] = count
        return count