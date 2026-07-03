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
        
        dfs(0, 0, -1)
        
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
        
        for i, j in trips:
            a = i
            b = j
            lca_node = LCA(a, b)
            path_set = set()
            while a != lca_node:
                path_set.add(a)
                a = parent[a]
            path_set.add(lca_node)
            while b != lca_node:
                if b in path_set:
                    break
                path_set.add(b)
                b = parent[b]
            for node in path_set:
                freq[node] += 1
        
        def dp(i, p):
            res0 = 0
            res1 = float('inf')
            for j in g[i]:
                if j == p:
                    continue
                child_res = dp(j, i)
                res0 += min(child_res[0], child_res[1])
                if res1 == float('inf'):
                    res1 = child_res[0] + price[i]
                else:
                    res1 = min(res1, child_res[0] + price[i], child_res[1] + (price[i] // 2))
            return (res0, res1)
        
        total_cost = 0
        for i in range(n):
            total_cost += freq[i] * price[i]
        ans = min(total_cost, dp(0, -1)[0] + price[0], dp(0, -1)[1])
        return ans