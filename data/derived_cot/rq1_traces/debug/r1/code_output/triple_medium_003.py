class Solution:
    def numMovStonesII(self, stones: List[int]) -> List[int]:
        stones.sort()
        n = len(stones)
        if n == 1:
            return [0, 0]
        move_penultimate = stones[-2] - stones[0] - n + 2
        move_final = stones[-1] - stones[1] - n + 2
        most_moves = max(move_penultimate, move_final)
        if stones[-1] - stones[0] == n - 1:
            return [0, 0]
        max_consec = 0
        left = 0
        for right in range(n):
            while stones[right] - stones[left] >= n:
                left += 1
            max_consec = max(max_consec, right - left + 1)
        min_moves = n - max_consec
        if max_consec == n - 1:
            if (stones[right] - stones[left] + 1 == n - 1) and (n - max_consec == 1):
                min_moves = 2
        return [min_moves, most_moves]