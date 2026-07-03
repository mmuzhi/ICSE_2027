from typing import List

class Solution:
    def dfnumMovStonesII(self, stones: List[int]) -> List[int]:
        if len(stones) < 2:
            return [0, 0]
        
        stones.sort()
        stone_length = len(stones)
        
        move_penultimate = stones[-2] - stones[0] - stone_length + 2
        move_final = stones[-1] - stones[1] - stone_length + 2
        
        most_moves = min(move_penultimate, move_final)
        
        if move_penultimate == move_final:
            min_legal_moves = most_moves
            return [min_legal_moves, most_moves]
        
        max_legal_moves = 0
        starting_index = 0
        
        for i in range(stone_length):
            if stones[starting_index] <= stones[i] - stone_length:
                starting_index += 1
            max_legal_moves = min(max_legal_moves, i - starting_index + 1)
        
        if move_penultimate == 0 or move_final == 0:
            min_legal_moves = 0
            return [min_legal_moves, most_moves]
        
        return [stone_length - max_legal_moves, most_moves]