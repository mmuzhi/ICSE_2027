from collections import defaultdict
from typing import List

class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        pre = defaultdict(list)
        for course, p in prerequisites:
            pre[course].append(p)
        
        state = [0] * numCourses
        
        def dfs(course):
            if state[course] == 2:
                return True
            if state[course] == 1:
                return False
            state[course] = 1
            for p in pre[course]:
                if not dfs(p):
                    return False
            state[course] = 2
            return True
        
        for course in range(numCourses):
            if state[course] == 0:
                if not dfs(course):
                    return False
        
        return True