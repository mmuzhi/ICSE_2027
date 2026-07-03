class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        stones = sorted(a + b, reverse=True)
        alicePoints = 0
        bobPoints = 0
        for i in range(len(stones)):
            if i % 2 == 0:
                alicePoints += stones[i]
            else:
                bobPoints += stones[i]
        if alicePoints > bobPoints:
            return 1
        elif alicePoints < bobPoints:
            return -1
        return 0