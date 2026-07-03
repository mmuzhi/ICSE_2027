from collections import defaultdict
from typing import List

class Solution:
    def cdist(self, it, distArray, distArrayIndex, edges):
        from collections import deque
        q = deque()
        q.append(it)
        distArray[it][distArrayIndex] = 0
        nodes = [it]
        while q:
            current = q.popleft()
            neighbor = edges[current]
            if neighbor == -1:
                continue
            if distArray[neighbor][distArrayIndex] == float('inf'):
                distArray[neighbor][distArrayIndex] = distArray[current][distArrayIndex] + 1
                q.append(neighbor)
                nodes.append(neighbor)
        return nodes

    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        INF = float('inf')
        dist = defaultdict(lambda: [INF, INF])
        mmin, ans = INF, INF
        
        n1 = self.cdist(node1, dist, 0, edges)
        n2 = self.cdist(node2, dist, 1, edges)
        combined = n1 + n2
        
        for k in combined:
            d1, d2 = dist[k]
            if d1 == INF or d2 == INF:
                continue
            m = max(d1, d2)
            if m < mmin:
                mmin = m
                ans = k
            elif m == mmin:
                ans = min(ans, k)
                
        return ans if ans != INF else -1