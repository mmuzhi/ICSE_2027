from typing import List

class Solution:
    def gridGame(self, grid: List[List[int]]) -> int:
        n = len(grid[0])
        prefix0 = [0] * (n + 1)
        prefix1 = [0] * (n + 1)
        
        for i in range(n):
            prefix0[i+1] = prefix0[i] + grid[0][i]
            prefix1[i+1] = prefix1[i] + grid[1][i]
        
        sum0 = prefix0[n]
        sum1 = prefix1[n]
        
        result = float('inf')
        
        for i in range(n):
            option1 = prefix0[i] + (sum1 - prefix1[i])
            option2 = prefix1[i+1] + (sum0 - prefix0[i+1])
            current_max = max(option1, option2)
            result = min(result, current_max)
        
        return result