from typing import List

class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        combines = [(a[i] + b[i], a[i], b[i]) for i in range(len(a))]
        combines.sort(reverse=True)
        bob_points = sum(b)
        alice_points = 0
        for i in range(0, len(combines), 2):
            alice_points += combines[i][1]
            bob_points -= combines[i][2]
        if alice_points > bob_points:
            return 1
        elif alice_points < bob_points:
            return -1
        return 0