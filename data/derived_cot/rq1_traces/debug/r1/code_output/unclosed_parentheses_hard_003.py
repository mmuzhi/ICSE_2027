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
        
        def dfs(i, l, p):
            level[i] = l
            parent[i] = p
            for j in g[i]:
                if j != p:
                    dfs(j, l + 1, i)
        
        def LCA(a, b):
            if level[a] > level[b]:
                a, b = b, a
            d = level[b] - level[a]
            while d > 0:
                b = parent[b]
                d -= 1
            if a == b:
                return a
            while a != b:
                a = parent[a]
                b = parent[b]
            return a
        
        dfs(0, 0, -1)
        for a, b in trips:
            lca_node = LCA(a, b)
            current = a
            while current != lca_node:
                freq[current] += 1
                current = parent[current]
            current = b
            while current != lca_node:
                freq[current] += 1
                current = parent[current]
            freq[lca_node] += 1
        
        def dp(i, p):
            res0 = 0  # current node not halved
            res1 = (price[i] // 2) * freq[i]  # current node halved
            for j in g[i]:
                if j != p:
                    curr = dp(j, i)
                    res0 += max(curr)
                    res1 += curr[0]
            return [res0, res1]
        
        total = sum(freq[i] * price[i] for i in range(n))
        max_saving = max(dp(0, -1))
        return total - max_saving