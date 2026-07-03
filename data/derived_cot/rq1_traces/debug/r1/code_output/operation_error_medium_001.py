from typing import List
from collections import defaultdict, deque

class Solution:
    def findAllRecipes(self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        # Create a mapping from recipe to its ingredients
        recipe_ingredients = {}
        n = len(recipes)
        for i in range(n):
            recipe_ingredients[recipes[i]] = ingredients[i]
        
        # Build the adjacency list and in-degree
        adj = defaultdict(list)
        in_degree = defaultdict(int)
        
        # Initialize in_degree for all recipes and their ingredients
        for recipe in recipes:
            in_degree[recipe] = 0  # Initialize recipes' in_degree to 0
        
        for i in range(n):
            for ing in ingredients[i]:
                adj[ing].append(recipes[i])  # ing is a prerequisite for the recipe
                in_degree[recipes[i]] += 1
                # Initialize in_degree for ingredients if not already present
                if ing not in in_degree:
                    in_degree[ing] = 0
        
        # Initialize the queue with all nodes with in_degree 0 (supplies and recipes with no dependencies)
        queue = deque()
        supply_set = set(supplies)
        for node in in_degree:
            if in_degree[node] == 0:
                # If the node is a supply or a recipe with no dependencies, add to queue
                if node in supply_set or node in recipe_ingredients:
                    queue.append(node)
        
        flst = []
        while queue:
            x = queue.popleft()
            
            # If x is a recipe, check if all its ingredients are in supplies
            if x in recipe_ingredients:
                required = recipe_ingredients[x]
                can_make = all(ing in supply_set for ing in required)
                if can_make:
                    flst.append(x)
                    supply_set.add(x)  # Add the recipe to supplies
            
            # Process the dependent recipes
            for neighbor in adj[x]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
        
        return flst