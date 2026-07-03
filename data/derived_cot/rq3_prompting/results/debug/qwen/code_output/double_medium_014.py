class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        from collections import defaultdict
        pre = defaultdict(list)
        for a, b in prerequisites:
            pre[a].append(b)
        
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
        
        for i in range(numCourses):
            if visited[i] == 0:
                if not dfs(i):
                    return False
        return True