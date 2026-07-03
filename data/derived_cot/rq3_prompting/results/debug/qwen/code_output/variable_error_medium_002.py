class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        stones = a + b
        stones.sort(reverse=True)
        alice = 0
        bob = 0
        for i in range(len(stones)):
            if i % 2 == 0:
                alice += stones[i]
            else:
                bob += stones[i]
        if alice > bob:
            return 1
        elif alice < bob:
            return -1
        else:
            return 0