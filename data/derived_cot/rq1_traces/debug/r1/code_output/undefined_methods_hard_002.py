class Solution:
    def isPossible(self, n: int, edges: list[list[int]]) -> bool:
        neighbors = [set() for _ in range(n)]
        for edge in edges:
            a, b = edge
            a -= 1
            b -= 1
            neighbors[a].add(b)
            neighbors[b].add(a)
        odd_degree_nodes = [i for i in range(n) if len(neighbors[i]) % 2 == 1]
        num_odd = len(odd_degree_nodes)
        if num_odd == 0:
            return True
        elif num_odd == 4:
            o1, o2, o3, o4 = odd_degree_nodes
            return ((o2 not in neighbors[o1] and o4 not in neighbors[o3]) or
                    (o3 not in neighbors[o1] and o4 not in neighbors[o2]) or
                    (o4 not in neighbors[o1] and o3 not in neighbors[o2]))
        elif num_odd == 2:
            o1, o2 = odd_degree_nodes
            if o2 not in neighbors[o1]:
                return True
            for x in range(n):
                if x != o1 and x != o2 and x not in neighbors[o1] and x not in neighbors[o2]:
                    return True
            return False
        return False