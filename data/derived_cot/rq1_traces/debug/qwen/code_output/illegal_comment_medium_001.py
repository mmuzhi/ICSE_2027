class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]):
        pre = defaultdict(list)
        for a, b in prerequisites:
            pre[a].append(b)
        
        visited = set()
        rec_stack = set()
        
        def dfs(course):
            visited.add(course)
            rec_stack.add(course)
            for p in pre[course]:
                if p not in visited:
                    if not dfs(p):
                        return False
                elif p in rec_stack:
                    return False
            rec_stack.remove(course)
            return True
        
        for course in range(numCourses):
            if course not in visited:
                if not dfs(course):
                    return False
        return True