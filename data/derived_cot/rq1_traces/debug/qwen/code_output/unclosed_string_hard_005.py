class Solution:
    def componentValue(self, nums: List[int], edges: List[List[int]]) -> int:
        n = len(nums)
        tree = [[] for _ in range(n)]
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        total = sum(nums)
        best = 0
        
        for cand in range(1, total // 2 + 1):
            if total % cand != 0:
                continue
            def dfs(u, parent):
                s = nums[u]
                for v in tree[u]:
                    if v == parent:
                        continue
                    s += dfs(v, u)
                return s if s >= cand else 0
            
            if dfs(0, -1) == 0:
                continue
            best = max(best, total // cand)
        
        return best