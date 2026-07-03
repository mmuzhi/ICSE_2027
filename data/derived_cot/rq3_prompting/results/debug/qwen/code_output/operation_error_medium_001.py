class Solution:
    def findAllRecipes(self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        from collections import defaultdict, deque
        
        graph = defaultdict(list)
        reverse_graph = defaultdict(list)
        indegree = defaultdict(int)
        
        n = len(recipes)
        
        for i in range(n):
            recipe = recipes[i]
            for ing in ingredients[i]:
                graph[recipe].append(ing)
                reverse_graph[ing].append(recipe)
                indegree[ing] += 1
        
        for recipe in recipes:
            indegree[recipe] = len(ingredients[recipes.index(recipe)])
        
        q = deque()
        for node in supplies:
            q.append(node)
        
        result = []
        while q:
            node = q.popleft()
            if node in recipes:
                result.append(node)
            for neighbor in reverse_graph.get(node, []):
                indegree[neighbor] -= 1
                if indegree[neighbor] == 0:
                    q.append(neighbor)
        
        return result