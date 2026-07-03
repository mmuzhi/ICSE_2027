from typing import List

class Solution:
    def checkValid(self, matrix: List[List[int]]) -> bool:
        n = len(matrix)
        expected = set(range(1, n + 1))
        
        # Check each row
        for row in matrix:
            if set(row) != expected:
                return False
        
        # Check each column by transposing the matrix
        for col in zip(*matrix):
            if set(col) != expected:
                return False
        
        return True