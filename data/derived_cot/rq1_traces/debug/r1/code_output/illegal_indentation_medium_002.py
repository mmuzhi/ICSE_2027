class Solution:
    def numMovesStonesII(self, stones: List[int]) -> List[int]:
        stones.sort()
        n = len(stones)
        move_penultimate = stones[-2] - stones[0] - n + 2
        move_final = stones[-1] - stones[1] - n + 2
        most_moves = max(move_penultimate, move_final)
        
        if move_penultimate == 0 or move_final == 0:
            min_legal = min(2, most_moves)
            return [min_legal, most_moves]
        
        max_legal = 0
        start = 0
        for i, stone in enumerate(stones):
            while stones[start] <= stone - n:
                start += 1
            current = i - start + 1
            max_legal = max(max_legal, current)
        
        return [n - max_legal, most_moves]