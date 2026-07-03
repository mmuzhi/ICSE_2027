from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1

        start = None
        end = None
        for node, d in degree.items():
            if d == 1:
                if start is None:
                    start = node
                else:
                    return []
            elif d == -1:
                if end is None:
                    end = node
                else:
                    return []
            elif d != 0:
                return []
        
        if not graph:
            return []
        
        if start is not None and end is not None and start != end:
            x = start
        elif start is None and end is None:
            x = next(iter(graph))
        else:
            return []
        
        ans = []
        def fn(x):
            while graph[x]:
                y = graph[x].pop()
                fn(y)
            ans.append(x)
        
        fn(x)
        ans.reverse()
        return [[ans[i], ans[i+1]] for i in range(len(ans)-1)]