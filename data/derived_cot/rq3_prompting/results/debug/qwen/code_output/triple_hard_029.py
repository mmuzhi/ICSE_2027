class Solution:
    def minimumTotalPrice(self, n: int, edges: List[List[int]], price: List[int], trips: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for i, j in edges:
            g[i].append(j)
            g[j].append(i)
            
        freq = [0] * n
        for trip in trips:
            for node in trip:
                freq[node] += 1
                
        level = [0] * n
        parent = [0] * n
        
        def dfs(i, l, p):
            level[i] = l
            parent[i] = p
            for j in g[i]:
                if j != p:
                    dfs(j, l + 1, i)
                    
        dfs(0, 0, -1)
        
        def dp(i, p):
            res0 = 0
            res1 = price[i] // 2 * freq[i]
            for j in g[i]:
                if j != p:
                    curr = dp(j, i)
                    res0 += max(curr)
                    res1 += curr[0]
            return [res0, res1]
        
        ans = 0
        for i in range(n):
            ans += freq[i] * price[i]
        return ans - max(dp(0, -1)[0], dp(0, -1)[1])