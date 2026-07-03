class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        n = len(edges)
        visited = [False] * n
        mx = -1
        
        for i in range(n):
            if not visited[i]:
                stack = [i]
                visited[i] = True
                depth = [-1] * n
                depth[i] = 0
                current_set = {i}
                while stack:
                    x = stack.pop()
                    y = edges[x]
                    if y == -1:
                        continue
                    if not visited[y]:
                        visited[y] = True
                        depth[y] = depth[x] + 1
                        stack.append(y)
                        current_set.add(y)
                    else:
                        if y in current_set:
                            cycle_length = depth[x] - depth[y] + 1
                            if cycle_length > mx:
                                mx = cycle_length
                for node in current_set:
                    depth[node] = -1
        return mx