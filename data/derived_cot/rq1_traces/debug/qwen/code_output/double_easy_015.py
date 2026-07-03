class Solution:
    def checkValid(self, matrix: List[List[int]]) -> bool:
        n = len(matrix)
        m = len(matrix[0])
        
        for i in range(n):
            if len(set(matrix[i])) != m:
                return False
        
        for j in range(m):
            col = [matrix[i][j] for i in range(n)]
            if len(set(col)) != n:
                return False
        
        return True