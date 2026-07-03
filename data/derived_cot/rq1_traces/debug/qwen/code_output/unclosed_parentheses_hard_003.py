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
            if level[a] < level[b]:
                a, b = b, a
            d = level[a] - level[b]
            while d:
                a = parent[a]
                d -= 1
            if a == b:
                return a
            while a != b:
                a = parent[a]
                b = parent[b]
            return a
        
        dfs(0, 0, -1)
        for i, j in trips:
            lca = LCA(i, j)
            path = []
            while i != lca:
                freq[i] += 1
                i = parent[i]
            freq[lca] += 1
            while j != lca:
                freq[j] += 1
                j = parent[j]
        
        def dp(i, p):
            dp0 = price[i] * freq[i]
            dp1 = float('inf')
            for j in g[i]:
                if j == p:
                    continue
                c0, c1 = dp(j, i)
                dp0 += c0
                dp1 = min(dp1, c1 + c0)
            if freq[i] >= 2:
                if dp0 == 0:
                    dp1 = min(dp1, (price[i] // 2) * freq[i])
                else:
                    dp1 = min(dp1, dp0 - price[i] * freq[i] + (price[i] // 2) * freq[i])
            return (dp0, dp1)
        
        dp0, dp1 = dp(0, -1)
        return dp1