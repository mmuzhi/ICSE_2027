class Solution:
    def cdist(self, start, distArray, distIndex, edges):
        rdist = 0
        it = start
        while it != -1 and distArray[it][distIndex] > rdist:
            distArray[it][distIndex] = rdist
            it = edges[it]
            rdist += 1
            
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        INF = float('inf')
        n = len(edges)
        dist = [[INF, INF] for _ in range(n)]
        self.cdist(node1, dist, 0, edges)
        self.cdist(node2, dist, 1, edges)
        mmin, ans = INF, INF
        for k in range(n):
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
        return ans if ans != float('inf') else -1