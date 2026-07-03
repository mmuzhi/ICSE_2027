from collections import defaultdict
from typing import List

class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        pre = defaultdict(list)
        for course, p in prerequisites:
            pre[course].append(p)
        
        visited = [0] * numCourses

        def dfs(course):
            if visited[course] == 1:
                return False
            if visited[course] == 2:
                return True
            visited[course] = 1
            for p in pre[course]:
                if not dfs(p):
                    return False
            visited[course] = 2
            return True
        
        for course in range(numCourses):
            if visited[course] == 0:
                if not dfs(course):
                    return False
        return True