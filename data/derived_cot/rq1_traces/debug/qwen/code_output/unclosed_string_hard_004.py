class Solution:
    def totalNQueens(self, n: int) -> int:
        def addans(board, ans):
            temp = []
            for row in board:
                for j in range(len(row)):
                    if row[j] == "Q":
                        temp.append(j + 1)
            ans.append(temp)
        
        def solve(row, board, low, upper, lower, ans, n):
            if row == n:
                addans(board, ans)
                return
            for col in range(n):
                if low[col] == 0 and upper[n - 1 + row - col] == 0 and lower[row + col] == 0:
                    board[row][col] = "Q"
                    low[col] = 1
                    upper[n - 1 + row - col] = 1
                    lower[row + col] = 1
                    solve(row + 1, board, low, upper, lower, ans, n)
                    low[col] = 0
                    upper[n - 1 + row - col] = 0
                    lower[row + col] = 0
        
        ans = []
        board = [["0"] * n for _ in range(n)]
        low = [0] * n
        upper = [0] * (2 * n - 1)
        lower = [0] * (2 * n - 1)
        solve(0, board, low, upper, lower, ans, n)
        return len(ans)