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

        def dfs(i: int, l: int, p: int):
            level[i] = l
            parent[i] = p
            for j in g[i]:
                if j != p:
                    dfs(j, l + 1, i)

        def lca(a: int, b: int) -> int:
            if level[a] > level[b]:
                a, b = b, a
            d = level[b] - level[a]
            while d:
                b = parent[b]
                d -= 1
            if a == b:
                return a
            while a != b:
                a = parent[a]
                b = parent[b]
            return a

        dfs(0, 0, -1)

        for u, v in trips:
            l = lca(u, v)
            # Increment frequency for all nodes on path u -> l (excluding l)
            while u != l:
                freq[u] += 1
                u = parent[u]
            # Increment frequency for all nodes on path v -> l (excluding l)
            while v != l:
                freq[v] += 1
                v = parent[v]
            # Increment lca once
            freq[l] += 1

        def dp(i: int, p: int):
            # res0: minimal total price for subtree if i is NOT halved
            # res1: minimal total price for subtree if i IS halved
            res0 = 0
            res1 = price[i] // 2 * freq[i]
            for j in g[i]:
                if j != p:
                    child = dp(j, i)
                    res0 += min(child[0], child[1])   # i not halved, child can be either
                    res1 += child[0]                  # i halved, child must NOT be halved
            return [res0, res1]

        root = dp(0, -1)
        return min(root[0], root[1])