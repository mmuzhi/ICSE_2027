class Solution:
    def gridGame(self, grid: List[List[int]]) -> int:
        n = len(grid[0])
        # Case 1: Start with top row
        max1 = 0
        for i in range(n):
            if i % 2 == 0:
                max1 = max(max1, grid[0][i])
            else:
                max1 = max(max1, grid[1][i])
        
        # Case 2: Start with bottom row
        max2 = 0
        for i in range(n):
            if i % 2 == 0:
                max2 = max(max2, grid[1][i])
            else:
                max2 = max(max2, grid[0][i])
        
        return min(max1, max2)