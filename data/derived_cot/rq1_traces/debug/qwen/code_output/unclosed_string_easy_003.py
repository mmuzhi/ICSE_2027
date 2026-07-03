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
                        c = rings[j-1]
                        if c == 'R':
                            rgb.append(c)
                        if c == 'G':
                            rgb.append(c)
                        if c == 'B':
                            rgb.append(c)
                if len(set(rgb)) == 3:
                    count += 1
        return count