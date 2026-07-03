class Solution:
    def numMagicSquaresInside(self, grid: List[List[int]]) -> int:
        M, N = len(grid), len(grid[0])
        res = 0
        
        for i in range(M - 2):
            for j in range(N - 2):
                arr = []
                for k in range(3):
                    arr.append(tuple(grid[i + k][j:j + 3]))
                
                nums = set()
                for row in arr:
                    for num in row:
                        nums.add(num)
                if nums != set(range(1, 10)):
                    continue
                
                if sum(arr[0]) != 15 or sum(arr[1]) != 15 or sum(arr[2]) != 15:
                    continue
                
                if arr[0][0] + arr[1][1] + arr[2][2] != 15 or \
                   arr[0][2] + arr[1][1] + arr[2][0] != 15:
                    continue
                
                if arr[0][0] + arr[1][0] + arr[2][0] != 15 or \
                   arr[0][1] + arr[1][1] + arr[2][1] != 15 or \
                   arr[0][2] + arr[1][2] + arr[2][2] != 15:
                    continue
                
                res += 1
        
        return res