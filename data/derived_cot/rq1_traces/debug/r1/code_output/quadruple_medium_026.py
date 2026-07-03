from collections import defaultdict, deque
from typing import List

class Solution:
    def findAllRecipes(self, recipes: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        # Create a mapping from recipe to its ingredients
        recipe_ingredients = {recipe: ingredients[i] for i, recipe in enumerate(recipes)}
        # Create sets for quick lookups
        supplies_set = set(supplies)
        recipes_set = set(recipes)
        # Build the graph and indegree
        dct = defaultdict(list)
        indegree = defaultdict(int)
        
        # Initialize indegree for all recipes
        for recipe in recipes:
            indegree[recipe] = 0
        
        # Populate the graph and adjust indegrees
        for i in range(len(recipes)):
            recipe = recipes[i]
            for ing in ingredients[i]:
                if ing in recipes_set:
                    dct[ing].append(recipe)
                    indegree[recipe] += 1
                else:
                    # If the ingredient is not a recipe and not a supply, mark recipe as impossible
                    if ing not in supplies_set:
                        indegree[recipe] = float('inf')  # Mark as impossible
        
        # Initialize the queue with recipes that have indegree 0
        queue = deque()
        for recipe in recipes:
            if indegree[recipe] == 0:
                queue.append(recipe)
        
        flst = []
        available = set(supplies)
        
        while queue:
            current = queue.popleft()
            # Check if all ingredients are available
            required = recipe_ingredients[current]
            can_make = all(ing in available for ing in required)
            
            if can_make:
                flst.append(current)
                available.add(current)
                # Process the neighbors
                for neighbor in dct[current]:
                    indegree[neighbor] -= 1
                    if indegree[neighbor] == 0:
                        queue.append(neighbor)
        
        return flst