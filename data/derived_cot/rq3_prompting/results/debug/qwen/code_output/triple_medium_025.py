class Solution:
    def cdist(self, it, distArray, distArrayIndex, edges):
        rdist = 0 
        nodes = []
        while it != -1 and distArray[it][distArrayIndex] > rdist:
            distArray[it][distArrayIndex] = rdist
            nodes.append(it)
            it = edges[it]
            rdist += 1
        return nodes
            
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        INF = float('inf')
        dist = defaultdict(lambda: [INF, INF])
        mmin, ans = INF, INF
               
        list1 = self.cdist(node1, dist, 0, edges)
        list2 = self.cdist(node2, dist, 1, edges)
                
        all_nodes = set(list1) | set(list2)
                
        for k in all_nodes:
            d1 = dist[k][0]
            d2 = dist[k][1]
            if d1 == INF or d2 == INF:
                continue
            m = max(d1, d2)
            if m < mmin: 
                mmin = m
                ans = k
            elif m == mmin: 
                ans = min(ans, k)
                    
        return ans if ans != INF else -1