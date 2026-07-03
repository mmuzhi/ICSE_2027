class Solution:
    def minimumTotalPrice(self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        freq = [0] * n
        level = [0] * n
        parent = [0] * n

        def dfs(i: int, l: int, p: int) -> None:
            level[i] = l
            parent[i] = p
            for j in g[i]:
                if j != p:
                    dfs(j, l + 1, i)

        def LCA(a: int, b: int) -> int:
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

        for start, end in trips:
            lca = LCA(start, end)
            x = start
            while x != lca:
                freq[x] += 1
                x = parent[x]
            freq[lca] += 1
            y = end
            while y != lca:
                freq[y] += 1
                y = parent[y]

        def dp(i: int, p: int):
            # [cost when i is not halved, cost when i is halved]
            not_halved = price[i] * freq[i]
            halved = (price[i] // 2) * freq[i]
            for j in g[i]:
                if j == p:
                    continue
                child = dp(j, i)
                not_halved += min(child[0], child[1])
                halved += child[0]   # neighbor cannot be halved
            return [not_halved, halved]

        root_choices = dp(0, -1)
        return min(root_choices)