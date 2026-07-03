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
            # update frequencies along the path
            x = start
            while x != lca:
                freq[x] += 1
                x = parent[x]
            freq[lca] += 1
            y = end
            while y != lca:
                freq[y] += 1
                y = parent[y]
        
        def dp(i: int, p: int) -> List[int]:
            # returns [max_saving if i not halved, max_saving if i halved]
            saving_i = (price[i] - price[i] // 2) * freq[i]
            res0 = 0          # saving when i not halved
            res1 = saving_i   # saving when i halved
            for j in g[i]:
                if j != p:
                    curr = dp(j, i)
                    res0 += max(curr)      # i not halved -> child can be in any state
                    res1 += curr[0]        # i halved -> child must not be halved
            return [res0, res1]
        
        total = sum(freq[i] * price[i])
        max_saving = max(dp(0, -1))
        return total - max_saving