class Solution:
    def dfnumMovStonesII(self, stones: List[int]) -> List[int]:
        n = len(stones)
        if n < 2:
            return []
        return [n-2, n-2]