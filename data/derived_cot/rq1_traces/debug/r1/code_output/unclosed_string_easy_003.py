class Solution:
    def countPoints(self, rings: str) -> int:
        lst = []
        count = 0
        for i in range(1, len(rings), 2):
            if rings[i] not in lst:
                lst.append(rings[i])
                rgb = []
                for j in range(1, len(rings), 2):
                    if rings[j] == rings[i]:
                        color = rings[j-1]
                        if color in {'R', 'G', 'B'}:
                            rgb.append(color)
                if len(set(rgb)) == 3:
                    count += 1
        return count