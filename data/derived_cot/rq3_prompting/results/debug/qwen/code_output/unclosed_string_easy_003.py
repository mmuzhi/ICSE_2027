class Solution:
    def countPoints(self, rings: str) -> int:
        lst = set()
        count = 0
        for i in range(1, len(rings), 2):
            if rings[i] not in lst:
                colors = set()
                for j in range(1, len(rings), 2):
                    if rings[j] == rings[i]:
                        colors.add(rings[j-1])
                if len(colors) == 3:
                    count += 1
                lst.add(rings[i])
        return count