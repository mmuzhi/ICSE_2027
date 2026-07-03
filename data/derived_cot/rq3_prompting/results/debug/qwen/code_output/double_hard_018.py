class Solution:
    def longestCycle(self, edges: List[int]) -> int:
        n = len(edges)
        if n == 0:
            return -1
        visited = [False] * n
        depth = [-1] * n
        time = 0
        mx = -1

        for i in range(n):
            if not visited[i]:
                stack = []
                stack.append((i, 0))
                visited[i] = True
                depth[i] = time
                time += 1
                current_stack = {i}
                while stack:
                    u, idx = stack[-1]
                    if idx < len(edges[u]):
                        v = edges[u][idx]
                        stack[-1] = (u, idx + 1)
                        if v == -1:
                            continue
                        if not visited[v]:
                            visited[v] = True
                            depth[v] = time
                            time += 1
                            stack.append((v, 0))
                            current_stack.add(v)
                        elif v in current_stack:
                            cycle_length = time - depth[v]
                            if cycle_length > mx:
                                mx = cycle_length
                    else:
                        stack.pop()
                        current_stack.remove(u)
        return mx