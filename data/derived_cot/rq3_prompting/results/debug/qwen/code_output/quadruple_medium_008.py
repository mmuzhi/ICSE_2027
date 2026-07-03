from typing import List
from collections import defaultdict

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
        
        nodes1 = self.cdist(node1, dist, 0, edges)
        nodes2 = self.cdist(node2, dist, 1, edges)
        n = nodes1 + nodes2
        
        for k in n:
            d1, d2 = dist[k]
            m = max(d1, d2)
            if m != INF:
                if m < mmin:
                    mmin = m
                    ans = k
                elif m == mmin:
                    ans = min(ans, k)
                    
        return ans if ans != INF else -1