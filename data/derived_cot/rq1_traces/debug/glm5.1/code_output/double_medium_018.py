from collections import defaultdict
from typing import List

class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:

        pre = defaultdict(list)
        for course, p in prerequisites:
            pre[course].append(p)
        
        visiting = set()
        visited = set()

        def dfs(course):
            if course in visiting:
                return False       
            if course in visited:
                return True
            if not pre[course]:
                visited.add(course)
                return True       
            
            visiting.add(course)
            for p in pre[course]:
                if not dfs(p): return False        
            visiting.remove(course)
            visited.add(course)
            return True
        
        for course in range(numCourses):
            if not dfs(course):
                return False
        return True