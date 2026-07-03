class Solution:
    # odd/even diameter couned individually
    def countSubgraphsForEachDiameter(self, n: int, edges: List[List[int]]) -> List[int]:
        adj = [[] for i in range(n)]
        for u,v in edges:
            adj[u-1].append(v-1)
            adj[v-1].append(u-1)
        def comb(p,q): # merge p and q, res[max(i,j)]+=p[i]*q[j]
            if len(q)<len(p): p,q = q,p
            res = [0]*len(q)
            res[0] = p[0]*q[0]
            for i in range(1,len(p)): p[i] += p[i-1]
            for i in range(1,len(q)): q[i] += q[i-1]
            for i in range(1,len(p)):
                res[i] = p[i]*q[i]-p[i-1]*q[i-1]
            for i in range(len(p),len(q)):
                res[i] = (q[i]-q[i-1])*p[-1]
            return res
            
        def dfs(r,p): # num of subtree rooted at r with given depth
            d = [1]
            for v in adj[r]:
                if v==p: continue
                t = [1]+dfs(v,r)
                d = comb(t,d)
            return d
        #end dfs
        ans = [0]*n
        # odd diameter with (u,v) as center edge
        for u,v in edges:
            u -= 1; v-=1
            p = dfs(u,v)
            q = dfs(v,u)
            for i in range(min(len(p),len(q))):
                if i+i+1 < n:
                    ans[i+i+1] += p[i]*q[i]
                    
        # even diameter with v as center vertex
        for v in range(n): 
            branches = []
            for u in adj[v]:
                branches.append(dfs(u, v))
            
            if not branches:
                continue
            
            all_d = [1]
            for b in branches:
                all_d = comb([1] + b, all_d)
            
            max_k = len(all_d)
            single_k = [0] * max_k
            
            for k in range(1, max_k):
                total_pref = 1
                prefs = []
                for b in branches:
                    pref = 1 + sum(b[:k-1])
                    prefs.append(pref)
                    total_pref *= pref
                
                for i, b in enumerate(branches):
                    if k - 1 < len(b):
                        single_k[k] += b[k-1] * (total_pref // prefs[i])
            
            for k in range(1, max_k):
                if 2*k < n:
                    ans[2*k] += all_d[k] - single_k[k]
        #end
        return ans[1:]