class Solution:
    def numMovesStonesII(self, stones: List[int]) -> List[int]:
        stones.sort()
        stone_length = len(stones)
        move_penultimate = stones[-2] - stones[0] - stone_length + 2
        move_final = stones[-1] - stones[1] - stone_length + 2
        most_moves = max(move_penultimate, move_final)
        
        if move_penultimate == 0 or move_final == 0:
            min_legal_moves = 2
        else:
            min_legal_moves = 1
            
        return [min_legal_moves, most_moves]