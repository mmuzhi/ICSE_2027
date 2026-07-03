class Solution:
    def isPossible(self, n: int, edges: list[list[int]]) -> bool:
        neighbors = [set() for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            neighbors[a].add(b)
            neighbors[b].add(a)
        oddDegNodes = [i for i in range(n) if len(neighbors[i]) % 2 == 1]
        numOdd = len(oddDegNodes)
        if numOdd == 0:
            return True
        if numOdd == 2:
            o1, o2 = oddDegNodes
            if o1 not in neighbors[o2]:
                return True
            # Check if there exists a node not connected to either
            for i in range(n):
                if i != o1 and i != o2 and i not in neighbors[o1] and i not in neighbors[o2]:
                    return True
            return False
        if numOdd == 4:
            a, b, c, d = oddDegNodes
            # Try all three possible pairings
            if (b not in neighbors[a] and d not in neighbors[c]) or \
               (c not in neighbors[a] and d not in neighbors[b]) or \
               (d not in neighbors[a] and c not in neighbors[b]):
                return True
            return False
        return False