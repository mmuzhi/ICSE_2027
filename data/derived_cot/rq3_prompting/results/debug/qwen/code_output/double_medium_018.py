class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        pre = defaultdict(list)
        for a, b in prerequisites:
            pre[b].append(a)
        
        taken = set()

        def dfs(course):
            if not pre[course]:
                return True
            if course in taken:
                return False
            taken.add(course)
            for p in pre[course]:
                if not dfs(p):
                    return False
            taken.remove(course)
            return True
        
        for course in range(numCourses):
            if not dfs(course):
                return False
        return True