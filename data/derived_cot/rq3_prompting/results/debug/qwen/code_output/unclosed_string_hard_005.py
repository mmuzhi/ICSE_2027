class Solution:
    def componentValue(self, nums: List[int], edges: List[List[int]]) -> int:
        n = len(nums)
        tree = [[] for _ in range(n)]
        for u, v in edges: 
            tree[u].append(v)
            tree[v].append(u)
        
        total = sum(nums)
        for cand in range(1, total//2 + 1):
            if total % cand == 0:
                def fn(u, p):
                    ans = nums[u]
                    for v in tree[u]:
                        if v == p:
                            continue
                        ans += fn(v, u)
                    return 0 if ans == cand else ans
                if fn(0, -1) == 0:
                    return total // cand
        return 0