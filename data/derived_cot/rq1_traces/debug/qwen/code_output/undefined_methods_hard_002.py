class Solution:
    def isPossible(self, n: int, edges: list[list[int]]) -> bool:
        if n == 0:
            return True
        neighbors = [set() for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            neighbors[a].add(b)
            neighbors[b].add(a)
        oddDegreesNodes = [i for i in range(n) if (len(neighbors[i]) % 2 == 1)]
        numOdd = len(oddDegreesNodes)
        if numOdd == 0 or numOdd == 2:
            return True
        return False