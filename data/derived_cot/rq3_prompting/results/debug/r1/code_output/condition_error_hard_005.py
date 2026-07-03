from typing import List

class Solution:
    def isPossible(self, n: int, edges: List[List[int]]) -> bool:
        neighbors = [set() for _ in range(n)]
        for a, b in edges:
            a -= 1
            b -= 1
            neighbors[a].add(b)
            neighbors[b].add(a)

        odd_degrees = [i for i in range(n) if len(neighbors[i]) % 2 == 1]
        num_odd = len(odd_degrees)

        if num_odd == 0:
            return True
        elif num_odd == 2:
            o1, o2 = odd_degrees
            # Case 1: two odd nodes are not connected -> add edge between them
            if o1 not in neighbors[o2]:
                return True
            # Case 2: they are connected -> need a third node not connected to at least one of them
            union = neighbors[o1] | neighbors[o2]
            # The set of possible third nodes (excluding o1 and o2) has size n-2.
            # If union covers all of them, no free node; otherwise we can add an edge.
            return len(union) != n - 2
        elif num_odd == 4:
            o1, o2, o3, o4 = odd_degrees
            # Adding an edge between any two non‑connected odd nodes reduces odd count to 2
            return (o1 not in neighbors[o2] or o1 not in neighbors[o3] or
                    o1 not in neighbors[o4] or o2 not in neighbors[o3] or
                    o2 not in neighbors[o4] or o3 not in neighbors[o4])
        else:
            return False