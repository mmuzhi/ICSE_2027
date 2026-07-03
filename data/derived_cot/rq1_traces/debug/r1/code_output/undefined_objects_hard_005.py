from typing import List

class Solution:
    def countSubgraphsForEachDiameter(self, n: int, edges: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u-1].append(v-1)
            adj[v-1].append(u-1)
        
        def comb(p, q):
            p_copy = list(p)
            q_copy = list(q)
            if len(q_copy) < len(p_copy):
                p_copy, q_copy = q_copy, q_copy
            res = [0] * len(q_copy)
            res[0] = p_copy[0] * q_copy[0]
            for i in range(1, len(p_copy)):
                p_copy[i] += p_copy[i-1]
            for i in range(1, len(q_copy)):
                q_copy[i] += q_copy[i-1]
            for i in range(1, len(p_copy)):
                res[i] = p_copy[i] * q_copy[i] - p_copy[i-1] * q_copy[i-1]
            for i in range(len(p_copy), len(q_copy)):
                res[i] = (q_copy[i] - q_copy[i-1]) * p_copy[-1] if p_copy else 0
            return res
        
        def dfs(r, parent):
            d = [1]
            for v in adj[r]:
                if v == parent:
                    continue
                child_depths = dfs(v, r)
                t = [1] + child_depths
                d = comb(t, d)
            return d
        
        ans = [0] * n
        # Odd diameter (center edge)
        for u, v in edges:
            u -= 1
            v -= 1
            p = dfs(u, v)
            q = dfs(v, u)
            max_len = min(len(p), len(q))
            for i in range(max_len):
                if i < len(p) and i < len(q):
                    ans[2 * i + 1] += p[i] * q[i]
        # Even diameter (center vertex)
        for v in range(n):
            if len(adj[v]) < 1:
                continue
            children = []
            parent = -1
            for neighbor in adj[v]:
                if len(adj[neighbor]) > 1:
                    children.append(neighbor)
                else:
                    parent = neighbor
            if len(children) < 1:
                continue
            first_child = children[0]
            tree = [1] + dfs(first_child, v)
            curr = [0] * n
            for u in children[1:]:
                q = [1] + dfs(u, v)
                for i in range(min(len(tree), len(q))):
                    curr[2 * i] += tree[i] * q[i]
                tree = comb(tree, q)
            for i in range(n):
                ans[i] += curr[i]
        return ans[1:n]