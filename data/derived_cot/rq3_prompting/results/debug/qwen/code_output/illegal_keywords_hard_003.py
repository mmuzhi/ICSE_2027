from collections import defaultdict

class Solution:
    def frogPosition(self, n: int, edges: list[list[int]], t: int, target: int) -> float:
        if not edges:
            return 1 if target == 1 else 0
        
        d = defaultdict(list)
        for i in edges:
            d[i[0]].append(i[1])
            d[i[1]].append(i[0])
        
        dp_prev = {1: 1.0}
        
        for _ in range(t):
            dp_curr = defaultdict(float)
            for node, prob in dp_prev.items():
                total = len(d.get(node, [])) + 1
                stay_prob = prob * (1.0 / total)
                dp_curr[node] += stay_prob
                for neighbor in d.get(node, []):
                    dp_curr[neighbor] += stay_prob
            dp_prev = dp_curr
        
        return dp_prev.get(target, 0.0)