class Solution:
    def countSubgraphsForEachDiameter(self, n: int, edges: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u-1].append(v-1)
            adj[v-1].append(u-1)
        
        def comb(p, q):
            res = [0] * (len(p) + len(q) - 1)
            for i in range(len(p)):
                for j in range(len(q)):
                    res[i+j] += p[i] * q[j]
            return res
        
        def dfs(r, p):
            d = [1]
            for v in adj[r]:
                if v == p:
                    continue
                t = dfs(v, r)
                t_shifted = [0] + t
                d = comb(d, t_shifted)
            return d
        
        ans = [0] * (n + 1)
        
        # Odd diameter: for each edge (u, v)
        for u, v in edges:
            u_idx = u - 1
            v_idx = v - 1
            p = dfs(u_idx, v_idx)
            q = dfs(v_idx, u_idx)
            for i in range(min(len(p), len(q))):
                if i < len(p) and i < len(q):
                    ans[i + i + 1] += p[i] * q[i]
        
        # Even diameter: for each vertex v
        for v in range(n):
            if len(adj[v]) == 1:
                continue
            components = []
            for w in adj[v]:
                comp = dfs(w, v)
                components.append(comp)
            total = [1]
            for comp in components:
                total = comb(total, comp)
            for i in range(min(len(total), n + 1)):
                ans[i + i] += total[i]
        
        return ans[1:]