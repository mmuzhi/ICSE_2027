from collections import defaultdict
from typing import List

class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # Build adjacency list: course -> list of prerequisites
        graph = defaultdict(list)
        for course, pre in prerequisites:
            graph[course].append(pre)

        # 0 = unvisited, 1 = visiting (in current recursion stack), 2 = fully processed
        state = [0] * numCourses

        def dfs(course: int) -> bool:
            if state[course] == 1:
                return False  # cycle detected
            if state[course] == 2:
                return True   # already verified as safe

            state[course] = 1          # mark as visiting
            for pre in graph[course]:
                if not dfs(pre):
                    return False
            state[course] = 2          # mark as processed
            return True

        for course in range(numCourses):
            if state[course] == 0:
                if not dfs(course):
                    return False
        return True