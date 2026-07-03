from collections import defaultdict, deque

class Solution:
    def findAllRecipes(self, recepies: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        if not recepies:
            return []
        recepies_set = set(recepies)
        n = len(recepies)
        graph = defaultdict(list)
        in_degree = {rec: 0 for rec in recepies}
        
        for i in range(n):
            for j in ingredients[i]:
                if j in recepies_set:
                    graph[j].append(recepies[i])
                    in_degree[recepies[i]] += 1
        
        initially_available = set()
        for i in range(n):
            valid = True
            for j in ingredients[i]:
                if j not in recepies_set and j not in supplies:
                    valid = False
                    break
            if valid:
                initially_available.add(recepies[i])
        
        Q = deque()
        for rec in in_degree:
            if rec in initially_available and in_degree[rec] == 0:
                Q.append(rec)
        
        available = set()
        while Q:
            node = Q.popleft()
            available.add(node)
            for neighbor in graph.get(node, []):
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    Q.append(neighbor)
        
        return list(available)