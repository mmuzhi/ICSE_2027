class Solution:
    def isPossible(self, n: int, edges: list[list[int]]) -> bool:
        neighbors = [set() for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -=1
            b -=1
            neighbors[a].add(b)
            neighbors[b].add(a)
        oddDegreesNodes = [i for i in range(n) if (len(neighbors[i]) % 2 == 1)]
        numOdd = len(oddDegreesNodes)
        if numOdd == 0:
            return True
        elif numOdd == 4:
            # Only possible if there are two pairs of vertices which are not connected
            o1, o2, o3, o4 = oddDegreesNodes
            if (o1 not in neighbors[o2] and o3 not in neighbors[o4]) or \
               (o1 not in neighbors[o3] and o2 not in neighbors[o4]) or \
               (o1 not in neighbors[o4] and o2 not in neighbors[o3]):
                return True
            return False
        elif numOdd == 2:
            # Only possible if both not connected or both connected but there is another node to connect to
            o1, o2 = oddDegreesNodes
            if o1 not in neighbors[o2]:
                 # Case 1: Not connected
                return True
            # Case 2: Find a node that is not connected to either o1 or o2
            if n - len(neighbors[o1] | neighbors[o2]) > 0:
                return True
            return False
        return False