from collections import defaultdict, deque
from typing import List

class Solution:
    def findAllRecipes(self, recepies: List[str], ingredients: List[List[str]], supplies: List[str]) -> List[str]:
        # Build graph: ingredient -> list of recipes that need it
        graph = defaultdict(list)
        indegree = {}
        recipe_set = set(recepies)

        for i, recipe in enumerate(recepies):
            indegree[recipe] = len(ingredients[i])  # number of ingredients required
            for ing in ingredients[i]:
                graph[ing].append(recipe)

        # Initialize queue with all supplies
        q = deque(supplies)
        available = set(supplies)
        result = []

        while q:
            item = q.popleft()
            for recipe in graph[item]:
                if recipe in indegree:
                    indegree[recipe] -= 1
                    if indegree[recipe] == 0:
                        # All ingredients are now available
                        result.append(recipe)
                        q.append(recipe)
                        available.add(recipe)

        return result