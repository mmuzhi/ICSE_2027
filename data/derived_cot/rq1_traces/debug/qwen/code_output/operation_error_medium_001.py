from collections import deque, defaultdict
from typing import List

class Solution:
    def findAllRecipes(self, recepies: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        # Build the set of nodes
        nodes = set(recepies) | set(supplies)
        
        # Build graph and in_degree
        graph = defaultdict(list)
        in_degree = defaultdict(int)
        
        # Initialize in_degree for all nodes to 0
        for node in nodes:
            in_degree[node] = 0
            
        n = len(recepies)
        # Build the graph and in_degree for recipes
        for i in range(n):
            recipe = recepies[i]
            for ing in ingredients[i]:
                graph[ing].append(recipe)
                in_degree[recipe] += 1
        
        # Start the Kahn's algorithm
        q = deque()
        for node in nodes:
            if in_degree[node] == 0:
                q.append(node)
                
        available = []
        
        while q:
            node = q.popleft()
            available.append(node)
            
            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    q.append(neighbor)
                    
        # Collect all recipes that are available
        result = [recipe for recipe in recepies if recipe in available]
        
        return result