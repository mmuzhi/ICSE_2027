from typing import List

class Solution:
    def gridGame(self, grid: List[List[int]]) -> int:
        result = float("inf")
        left = 0
        right = sum(grid[0])
        for a, b in zip(grid[1], grid[0]):
            top_suffix = right - b
            result = min(result, max(left, top_suffix))
            left += a
            right -= b
        return result