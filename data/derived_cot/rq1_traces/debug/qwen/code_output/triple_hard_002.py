class Solution:
    def componentValue(self, nums: List[int], edges: List[List[int]]) -> int:
        n = len(nums)
        tree = [[] for _ in range(n)]
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)
        
        total = sum(nums)
        for cand in range(1, total//2 + 1):
            if total % cand != 0:
                continue
            def dfs(u, p):
                s = nums[u]
                for v in tree[u]:
                    if v == p:
                        continue
                    s += dfs(v, u)
                return 0 if s == cand else s
            if dfs(0, -1) == 0:
                return total // cand - 1
        return 0