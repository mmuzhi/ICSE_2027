class Solution:
    def gridGame(self, grid: List[List[int]]) -> int: 
        left = 0
        right = sum(grid[1])
        result = float('inf')
        
        for a, b in zip(grid[0], grid[1]):
            left += a
            right -= b
            result = min(result, max(left, right))
        
        return result