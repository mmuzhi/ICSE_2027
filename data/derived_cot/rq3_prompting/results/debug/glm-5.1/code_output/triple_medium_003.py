from typing import List

class Solution:
    def numMovesStonesII(self, stones: List[int]) -> List[int]:
        stones.sort()
        stone_len = len(stones)
        move_penultimate = stones[-2] - stones[0] - stone_len + 2
        move_final = stones[-1] - stones[1] - stone_len + 2
        most_moves = max(move_penultimate, move_final)
        
        max_legal_moves = 0
        starting_index = 0
        for index, stone in enumerate(stones):
            while stones[starting_index] <= stone - stone_len:
                starting_index += 1
            max_legal_moves = min(max(max_legal_moves, index - starting_index + 1), stone_len)
            
        return [stone_len - max_legal_moves, most_moves]

solution = Solution()
print(solution.numMovesStonesII([7, 4, 9]))