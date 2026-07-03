from collections import deque, defaultdict

class Solution:
    def findAllRecipes(self, recepies: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        graph = defaultdict(list)
        reverse_graph = defaultdict(list)
        base_supplies_set = set(supplies)
        n = len(recepies)
        
        for i in range(n):
            recipe = recepies[i]
            ingredients_list = ingredients[i]
            graph[recipe] = ingredients_list
            for ing in ingredients_list:
                reverse_graph[ing].append(recipe)
        
        indegree = {}
        for recipe in graph:
            count = 0
            for ing in graph[recipe]:
                if ing not in base_supplies_set:
                    count += 1
            indegree[recipe] = count
        
        q = deque()
        for recipe in graph:
            if indegree[recipe] == 0:
                q.append(recipe)
        
        result = []
        while q:
            r = q.popleft()
            result.append(r)
            for dep in reverse_graph.get(r, []):
                if dep in graph:
                    indegree[dep] -= 1
                    if indegree[dep] == 0:
                        q.append(dep)
        
        return result