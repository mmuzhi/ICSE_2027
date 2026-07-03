class Solution:
    def checkValid(self, matrix: List[List[int]]) -> bool:
        n = len(matrix)
        m = len(matrix[0])
        dp_row = [[False] * m for _ in range(n)]
        dp_col = [[False] * m for _ in range(n)]

        for i in range(n):
            for j in range(m):
                if dp_row[i][j] or dp_col[i][j]:
                    return False
                dp_row[i][j] = True
                dp_col[i][j] = True
        return True