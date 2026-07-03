class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        graph = [[] for _ in range(numCourses)]
        for a, b in prerequisites:
            graph[b].append(a)
        
        visited = [False] * numCourses
        recStack = set()
        
        def dfs(course):
            if visited[course]:
                return True
            if course in recStack:
                return False
            
            visited[course] = True
            recStack.add(course)
            for p in graph[course]:
                if not dfs(p):
                    return False
            recStack.remove(course)
            return True
        
        for i in range(numCourses):
            if not visited[i]:
                if not dfs(i):
                    return False
        return True