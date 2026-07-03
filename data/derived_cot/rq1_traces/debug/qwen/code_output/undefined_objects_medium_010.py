class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        base = [a[i] + b[i] for i in range(len(a))]
        base.sort(reverse=True)
        alice = 0
        bob = 0
        for i in range(len(a)):
            if i % 2 == 0:
                alice += base[i]
            else:
                bob += base[i]
        if alice > bob:
            return 1
        elif alice < bob:
            return -1
        else:
            return 0