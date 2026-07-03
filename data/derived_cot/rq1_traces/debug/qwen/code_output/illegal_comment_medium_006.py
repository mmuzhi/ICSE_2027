class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        M = len(grid)
        N = len(grid[0])
        res = 0
        
        if M < 3 or N < 3:
            return 0
        
        for i in range(M - 2):
            for j in range(N - 2):
                square = []
                for x in range(3):
                    square.append(grid[i + x][j:j + 3])
                
                nums = []
                for row in square:
                    nums.extend(row)
                
                if set(nums) != set(range(1, 10)):
                    continue
                
                if sum(square[0]) != 15 or sum(square[1]) != 15 or sum(square[2]) != 15:
                    continue
                
                if square[0][0] + square[1][0] + square[2][0] != 15:
                    continue
                if square[0][1] + square[1][1] + square[2][1] != 15:
                    continue
                if square[0][2] + square[1][2] + square[2][2] != 15:
                    continue
                
                if square[0][0] + square[1][1] + square[2][2] != 15:
                    continue
                if square[0][2] + square[1][1] + square[2][0] != 15:
                    continue
                
                res += 1
        
        return res