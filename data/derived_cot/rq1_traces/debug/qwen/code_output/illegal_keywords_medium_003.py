from collections import deque
from typing import List, Dict, DefaultDict
from collections import defaultdict

class Solution:
    def cdist(self, it, distArray, distArrayIndex, edges):
        q = deque([it])
        distArray[it][distArrayIndex] = 0
        while q:
            node = q.popleft()
            neighbor = edges[node]
            if neighbor == -1:
                continue
            if distArray[neighbor][distArrayIndex] == float('inf'):
                distArray[neighbor][distArrayIndex] = distArray[node][distArrayIndex] + 1
                q.append(neighbor)
    
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        INF = float('inf')
        dist = defaultdict(lambda: [INF, INF])
        mmin, ans = INF, -1
        
        self.cdist(node1, dist, 0, edges)
        self.cdist(node2, dist, 1, edges)
        
        for node in dist:
            d1, d2 = dist[node]
            if d1 != INF and d2 != INF:
                max_dist = max(d1, d2)
                if max_dist < mmin:
                    mmin = max_dist
                    ans = node
                elif max_dist == mmin:
                    if node < ans:
                        ans = node
        
        return ans if ans != -1 else -1