from collections import deque
from typing import List

class Solution:
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        n = len(edges)
        INF = float('inf')
        d1 = [INF] * n
        d2 = [INF] * n
        
        # BFS for node1
        q = deque()
        q.append(node1)
        d1[node1] = 0
        while q:
            cur = q.popleft()
            nxt = edges[cur]
            if nxt == -1:
                continue
            if nxt < 0 or nxt >= n:
                continue
            if d1[nxt] == INF:
                d1[nxt] = d1[cur] + 1
                q.append(nxt)
        
        # BFS for node2
        q = deque()
        q.append(node2)
        d2[node2] = 0
        while q:
            cur = q.popleft()
            nxt = edges[cur]
            if nxt == -1:
                continue
            if nxt < 0 or nxt >= n:
                continue
            if d2[nxt] == INF:
                d2[nxt] = d2[cur] + 1
                q.append(nxt)
        
        ans = -1
        mmin = INF
        for i in range(n):
            if d1[i] != INF and d2[i] != INF:
                m = max(d1[i], d2[i])
                if m < mmin:
                    mmin = m
                    ans = i
                elif m == mmin:
                    if i < ans:
                        ans = i
        
        return ans