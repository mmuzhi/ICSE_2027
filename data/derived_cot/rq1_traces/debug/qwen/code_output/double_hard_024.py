class Solution:
    def minimumTotalPrice(self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for i, j in edges:
            g[i].append(j)
            g[j].append(i)
            
        parent = [-1] * n
        level = [0] * n
        stack = [0]
        parent[0] = -1
        while stack:
            node = stack.pop()
            for neighbor in g[node]:
                if neighbor == parent[node]:
                    continue
                parent[neighbor] = node
                level[neighbor] = level[node] + 1
                stack.append(neighbor)
        
        def LCA(a, b):
            if level[a] < level[b]:
                a, b = b, a
            while level[a] > level[b]:
                a = parent[a]
            while a != b:
                a = parent[a]
                b = parent[b]
            return a
        
        freq = [0] * n
        for i, j in trips:
            a = i
            b = j
            l = LCA(a, b)
            while a != l:
                freq[a] += 1
                a = parent[a]
            freq[l] += 1
            while b != l:
                freq[b] += 1
                b = parent[b]
        
        def dp(i, p):
            res0 = 0
            res1 = price[i] // 2 * freq[i]
            for j in g[i]:
                if j == p:
                    continue
                curr = dp(j, i)
                res0 += max(curr)
                res1 += curr[0]
            return (res0, res1)
        
        ans = 0
        for i in range(n):
            ans += freq[i] * price[i]
        res = dp(0, -1)
        return ans - max(res)