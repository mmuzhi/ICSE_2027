class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        combines = [(a[i] + b[i], a[i], b[i]) for i in range(len(a))]
        combines.sort(reverse=True)
        alice = 0
        bob = 0
        for i in range(len(a)):
            if i % 2 == 0:
                alice += combines[i][1]
            else:
                bob += combines[i][2]
        if alice > bob:
            return 1
        elif alice < bob:
            return -1
        else:
            return 0