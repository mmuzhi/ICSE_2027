from collections import defaultdict
from typing import List

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        non_zero = [k for k, d in degree.items() if d != 0]
        
        if len(non_zero) == 0:
            start = next(iter(degree.keys()))
        elif len(non_zero) == 2:
            if set(degree[k] for k in non_zero) != {1, -1}:
                return []
            start = non_zero[0] if degree[non_zero[0]] == 1 else non_zero[1]
        else:
            return []
        
        ans = []
        
        def fn(x):
            while graph[x]:
                y = graph[x].pop()
                fn(y)
            ans.append(x)
        
        fn(start)
        ans.reverse()
        
        result = []
        for i in range(len(ans) - 1):
            result.append([ans[i], ans[i+1]])
        
        return result