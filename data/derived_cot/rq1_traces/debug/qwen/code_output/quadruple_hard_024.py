from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        graph = defaultdict(list)
        degree = defaultdict(int)
        
        for x, y in pairs:
            graph[x].append(y)
            degree[x] += 1
            degree[y] -= 1
        
        count_1 = 0
        count_neg1 = 0
        for node, d in degree.items():
            if d == 1:
                count_1 += 1
            elif d == -1:
                count_neg1 += 1
            elif d != 0:
                return []
        
        start = None
        end = None
        
        if count_1 == 1 and count_neg1 == 1:
            for node, d in degree.items():
                if d == 1:
                    start = node
                elif d == -1:
                    end = node
        elif count_1 == 0 and count_neg1 == 0:
            if not graph:
                return []
            start = next(iter(graph.keys()))
        else:
            return []
        
        ans = []
        
        def fn(x):
            while graph[x]:
                fn(graph[x].pop())
            ans.append(x)
        
        fn(start)
        ans.reverse()
        
        result = []
        for i in range(len(ans) - 1):
            result.append([ans[i], ans[i+1]])
        
        return result