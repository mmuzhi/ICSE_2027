from typing import List

class Solution:
    def checkValid(self, matrix: List[List[int]]) -> bool:
        n = len(matrix)
        dp_row = [[False] * n for _ in range(n)]
        dp_col = [[False] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                val = matrix[i][j]
                if dp_row[i][val - 1] or dp_col[j][val - 1]:
                    return False
                dp_row[i][val - 1] = True
                dp_col[j][val - 1] = True
        return True