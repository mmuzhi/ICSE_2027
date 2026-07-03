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
        for i, j in trips:
            lca = LCA(i, j)
            temp = i
            while temp != lca:
                freq[temp] += 1
                temp = parent[temp]
            freq[lca] += 1
            temp = j
            while temp != lca:
                freq[temp] += 1
                temp = parent[temp]
        
        def dp(i, p):
            if freq[i] > 0:
                res0 = price[i]
                for j in g[i]:
                    if j != p:
                        curr = dp(j, i)
                        res0 += min(curr[0], curr[1])
                return [res0, float('inf')]
            else:
                res0 = price[i]
                res1 = price[i] // 2
                for j in g[i]:
                    if j != p:
                        curr = dp(j, i)
                        res0 += min(curr[0], curr[1])
                        res1 += min(curr[0], curr[1])
                return [res0, res1]
        
        res = dp(0, -1)
        if res[1] == float('inf'):
            return res[0]
        else:
            return min(res[0], res[1])