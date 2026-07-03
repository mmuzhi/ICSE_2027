class Solution:
    def componentValue(self, nums: List[int], edges: List[List[int]]) -> int:
        n = len(nums)
        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        total = sum(nums)
        if total == 0:
            return n - 1
        
        ans = 0
        for cand in range(1, total // 2 + 1):
            if total % cand != 0:
                continue
            def dfs(u, parent):
                s = nums[u]
                for v in graph[u]:
                    if v == parent:
                        continue
                    s += dfs(v, u)
                if s == cand:
                    return 0
                return s
            if dfs(0, -1) == 0:
                ans = total // cand
                break
        return ans