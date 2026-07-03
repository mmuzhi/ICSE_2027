class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        pre = defaultdict(list)
        for a, b in prerequisites:
            pre[b].append(a)
        
        visited = set()
        rec_stack = set()
        
        def dfs(course):
            if course in rec_stack:
                return False
            if course in visited:
                return True
            
            visited.add(course)
            rec_stack.add(course)
            
            if course not in pre:
                rec_stack.remove(course)
                return True
            
            for p in pre[course]:
                if not dfs(p):
                    return False
            
            rec_stack.remove(course)
            return True
        
        for course in range(numCourses):
            if course not in visited:
                if not dfs(course):
                    return False
        
        return True