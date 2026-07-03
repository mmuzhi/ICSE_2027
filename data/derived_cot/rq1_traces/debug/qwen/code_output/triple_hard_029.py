class Solution:
    def minimumTotalPrice(self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for i, j in edges:
            g[i].append(j)
            g[j].append(i)
            
        freq = [0] * n
        parent = [-1] * n
        level = [-1] * n
        
        from collections import deque
        dq = deque([0])
        level[0] = 0
        parent[0] = -1
        while dq:
            i = dq.popleft()
            for j in g[i]:
                if level[j] == -1:
                    level[j] = level[i] + 1
                    parent[j] = i
                    dq.append(j)
                    
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
            l = lca(i, j)
            node = i
            while node != l:
                freq[node] += 1
                node = parent[node]
            freq[l] += 1
            node = j
            while node != l:
                freq[node] += 1
                node = parent[node]
        
        def dfs(i, p):
            res0 = price[i] * freq[i]
            res1 = (price[i] // 2) * freq[i]
            for j in g[i]:
                if j == p:
                    continue
                child0, child1 = dfs(j, i)
                res0 += min(child0, child1)
                res1 += min(child0, child1)
            return (res0, res1)
        
        if n == 0:
            return 0
        total = 0
        for i in range(n):
            total += price[i] * freq[i]
        root0, root1 = dfs(0, -1)
        return min(root0, root1)