from collections import deque
from typing import List

class Solution:
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        n = len(edges)
        if n == 0:
            return -1
        
        dist1 = [-1] * n
        dist2 = [-1] * n
        
        q1 = deque()
        dist1[node1] = 0
        q1.append(node1)
        while q1:
            cur = q1.popleft()
            nxt = edges[cur]
            if nxt == -1:
                continue
            if dist1[nxt] == -1:
                dist1[nxt] = dist1[cur] + 1
                q1.append(nxt)
                
        q2 = deque()
        dist2[node2] = 0
        q2.append(node2)
        while q2:
            cur = q2.popleft()
            nxt = edges[cur]
            if nxt == -1:
                continue
            if dist2[nxt] == -1:
                dist2[nxt] = dist2[cur] + 1
                q2.append(nxt)
                
        ans = -1
        min_max = float('inf')
        for i in range(n):
            if dist1[i] != -1 and dist2[i] != -1:
                max_dist = max(dist1[i], dist2[i])
                if max_dist < min_max:
                    min_max = max_dist
                    ans = i
                elif max_dist == min_max and i < ans:
                    ans = i
                    
        return ans