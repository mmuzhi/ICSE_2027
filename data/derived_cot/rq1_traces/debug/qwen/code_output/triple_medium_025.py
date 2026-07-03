class Solution:
    def cdist(self, it, distArray, distArrayIndex, edges):
        rdist = 0
        while it != -1 and distArray[it][distArrayIndex] > rdist:
            distArray[it][distArrayIndex] = rdist
            it = edges[it]
            rdist += 1
            
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        INF = float('inf')
        n = len(edges)
        dist = [[INF, INF] for _ in range(n)]
        
        self.cdist(node1, dist, 0, edges)
        self.cdist(node2, dist, 1, edges)
        
        mmin = INF
        ans = -1
        for i in range(n):
            if dist[i][0] != INF and dist[i][1] != INF:
                m = max(dist[i][0], dist[i][1])
                if m < mmin:
                    mmin = m
                    ans = i
                elif m == mmin:
                    if ans == -1 or i < ans:
                        ans = i
        
        if mmin == INF:
            return -1
        return ans