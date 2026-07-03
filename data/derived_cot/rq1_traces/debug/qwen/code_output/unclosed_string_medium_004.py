class Solution:
    def gridGame(self, grid: List[List[int]]) -> int:
        n = len(grid[0])
        if n == 0:
            return 0
        
        prefix_max0 = [0] * n
        prefix_max0[0] = grid[0][0]
        for i in range(1, n):
            prefix_max0[i] = max(prefix_max0[i-1], grid[0][i])
        
        suffix_max1 = [0] * n
        suffix_max1[-1] = grid[1][-1]
        for i in range(n-2, -1, -1):
            suffix_max1[i] = max(suffix_max1[i+1], grid[1][i])
        
        ans = float('inf')
        for j in range(n):
            if j == 0:
                first_max = float('-inf')
            else:
                first_max = prefix_max0[j-1]
            second_max = suffix_max1[j]
            candidate = max(first_max, second_max)
            if candidate < ans:
                ans = candidate
        
        return ans