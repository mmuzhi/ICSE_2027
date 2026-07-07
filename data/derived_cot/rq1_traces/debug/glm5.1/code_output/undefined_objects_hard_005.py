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
                ans[i+i+1] += p[i]*q[i]
        #even diamter with v as center vertex
        for v in range(n): 
            if len(adj[v])==1: continue 
            tree = [1]+dfs(adj[v][0],v) #tree with depth
            curr = [0]*n
            for u in adj[v][1:]:
                q = [1]+dfs(u,v)
                q_prefix = [0] * len(q)
                q_prefix[0] = q[0]
                for i in range(1, len(q)):
                    q_prefix[i] = q_prefix[i-1] + q[i]
                
                new_curr = [0]*n
                max_k = (n - 1) // 2 + 1
                for k in range(1, max_k):
                    sum_q = q_prefix[k-1] if k-1 < len(q) else q_prefix[-1]
                    tree_k = tree[k] if k < len(tree) else 0
                    q_k = q[k] if k < len(q) else 0
                    new_curr[2*k] = curr[2*k] * sum_q + tree_k * q_k
                    
                curr = new_curr
                tree = comb(tree,q)
            for i in range(2,n,2):
                ans[i] += curr[i]
        #end
        return ans[1:]