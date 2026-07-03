class Solution:
    def checkValid(self, matrix: List[List[int]]) -> bool:
        n = len(matrix)
        for i in range(n):
            row_seen = [False] * (n + 1)
            col_seen = [False] * (n + 1)
            for j in range(n):
                if row_seen[matrix[i][j]] or col_seen[matrix[j][i]]:
                    return False
                row_seen[matrix[i][j]] = True
                col_seen[matrix[j][i]] = True
        return True