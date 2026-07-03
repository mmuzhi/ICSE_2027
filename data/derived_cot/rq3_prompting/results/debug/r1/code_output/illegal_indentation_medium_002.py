from typing import List

class Solution:
    def numMovesStonesII(self, stones: List[int]) -> List[int]:
        stones.sort()
        n = len(stones)
        max_moves = max(stones[-1] - stones[1] - n + 2, stones[-2] - stones[0] - n + 2)
        
        i = 0
        min_moves = n
        for j in range(n):
            while stones[j] - stones[i] >= n:
                i += 1
            count = j - i + 1
            if count == n - 1 and stones[j] - stones[i] == n - 2:
                min_moves = min(min_moves, 2)
            else:
                min_moves = min(min_moves, n - count)
        
        return [min_moves, max_moves]