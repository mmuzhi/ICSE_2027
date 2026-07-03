class Solution:
    def isPossible(self, n: int, edges: list[list[int]]) -> bool:
        neighbors = [set() for _ in range(n)]
        for a, b in edges:
            a -= 1
            b -= 1
            neighbors[a].add(b)
            neighbors[b].add(a)
        oddDegreesNodes = [i for i in range(n) if (len(neighbors[i]) % 2 == 1)]
        numOdd = len(oddDegreesNodes)
        if numOdd == 0:
            return True
        elif numOdd == 2:
            o1, o2 = oddDegreesNodes
            if o2 not in neighbors[o1]:
                return True
            # Need a node c such that both edges (o1,c) and (o2,c) can be added
            for c in range(n):
                if c == o1 or c == o2:
                    continue
                if c not in neighbors[o1] and c not in neighbors[o2]:
                    return True
            return False
        elif numOdd == 4:
            a, b, c, d = oddDegreesNodes
            # Three possible pairings of the four odd nodes
            if b not in neighbors[a] and d not in neighbors[c]:
                return True
            if c not in neighbors[a] and d not in neighbors[b]:
                return True
            if d not in neighbors[a] and c not in neighbors[b]:
                return True
            return False
        else:
            return False