from queue import Queue

class Solution:
    def frogPosition(self, n: int, edges: list[list[int]], t: int, target: int) -> float:
        if n < 1:
            return 0.0
        
        d = {i: [] for i in range(1, n+1)}
        for edge in edges:
            u, v = edge[0], edge[1]
            d[u].append(v)
            d[v].append(u)
        
        visit = [0] * (n+1)
        q = Queue()
        q.put([1, 1.0])
        visit[1] = 1
        
        for dur in range(t):
            l = q.qsize()
            for _ in range(l):
                temp = q.get()
                node, prob = temp[0], temp[1]
                count = 0
                for neighbor in d[node]:
                    if visit[neighbor] == 0:
                        count += 1
                
                if node == target and count == 0:
                    return prob
                
                for neighbor in d[node]:
                    if visit[neighbor] == 0:
                        q.put([neighbor, prob * (1.0 / count)])
        
        while not q.empty():
            temp = q.get()
            if temp[0] == target:
                return temp[1]
        
        return 0.0