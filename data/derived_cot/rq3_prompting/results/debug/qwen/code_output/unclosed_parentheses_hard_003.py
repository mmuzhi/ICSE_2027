from typing import List

class Solution:
    def minimumTotalPrice(self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for i, j in edges:
            g[i].append(j)
            g[j].append(i)
        
        freq = [0] * n
        level = [0] * n
        parent = [0] * n
        
        stack = [0]
        level[0] = 0
        parent[0] = -1
        while stack:
            i = stack.pop()
            for j in g[i]:
                if j == parent[i]:
                    continue
                parent[j] = i
                level[j] = level[i] + 1
                stack.append(j)
        
        def lca(a, b):
            if level[a] < level[b]:
                a, b = b, a
            while level[a] > level[b]:
                a = parent[a]
            if a == b:
                return a
            while a != b:
                a = parent[a]
                b = parent[b]
            return a
        
        for i, j in trips:
            lca_node = lca(i, j)
            temp = i
            while temp != lca_node:
                freq[temp] += 1
                temp = parent[temp]
            freq[lca_node] += 1
            temp = j
            while temp != lca_node:
                freq[temp] += 1
                temp = parent[temp]
        
        total = 0
        for i in range(n):
            total += price[i] * freq[i]
        return total