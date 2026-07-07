from typing import List

class Solution:
    def numMovesStonesII(self, stones: List[int]) -> List[int]:
        stones.sort()
        stone_length = len(stones)
        move_penultimate = stones[-2] - stones[0] - stone_length + 2
        move_final = stones[-1] - stones[1] - stone_length + 2
        most_moves = max(move_penultimate, move_final)
        
        min_legal_moves = stone_length
        starting_index = 0
        for index, stone in enumerate(stones):
            while stones[starting_index] <= stone - stone_length:
                starting_index += 1
            max_legal_moves = index - starting_index + 1
            if max_legal_moves == stone_length - 1 and stone - stones[starting_index] + 1 == stone_length - 1:
                min_legal_moves = min(min_legal_moves, 2)
            else:
                min_legal_moves = min(min_legal_moves, stone_length - max_legal_moves)
                
        return [min_legal_moves, most_moves]

solution = Solution()
print(solution.numMovesStonesII([7, 4, 9]))