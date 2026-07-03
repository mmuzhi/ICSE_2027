class Solution:
    def componentValue(self, nums: List[int], edges: List[List[int]]) -> int:
        n = len(nums)
        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        total = sum(nums)
        ans = 0
        
        for k in range(n, 0, -1):
            if total < k * (total // k):
                continue
            min_sum = total // k
            
            def dfs(u, parent):
                s = nums[u]
                for v in graph[u]:
                    if v == parent:
                        continue
                    s += dfs(v, u)
                if s < min_sum:
                    return 0
                else:
                    return s
            
            components = 0
            try:
                for i in range(n):
                    if dfs(i, -1) > 0:
                        components += 1
                if components >= k:
                    ans = k
                    break
            except Exception as e:
                pass
        return ans