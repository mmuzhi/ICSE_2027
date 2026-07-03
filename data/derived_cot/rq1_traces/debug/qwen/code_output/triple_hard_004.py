from typing import List
from collections import defaultdict

class Solution:
    def validArrangement(self, pairs: List[List[int]]) -> List[List[int]]:
        if not pairs:
            return []
        
        graph = defaultdict(list)
        out_degree = defaultdict(int)
        in_degree = defaultdict(int)
        nodes = set()
        
        for x, y in pairs:
            graph[x].append(y)
            out_degree[x] += 1
            in_degree[y] += 1
            nodes.add(x)
            nodes.add(y)
        
        start = None
        end = None
        for node in nodes:
            net = out_degree[node] - in_degree[node]
            if net == 1:
                start = node
            elif net == -1:
                end = node
            elif net != 0:
                return []
        
        if not nodes:
            return []
        
        undir_graph = {node: [] for node in nodes}
        for x, y in pairs:
            undir_graph[x].append(y)
            undir_graph[y].append(x)
        
        visited = set()
        stack = [next(iter(nodes))]
        visited.add(stack[0])
        while stack:
            node = stack.pop()
            for neighbor in undir_graph[node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    stack.append(neighbor)
        
        if visited != nodes:
            return []
        
        stack = []
        if start is not None:
            stack.append(start)
        else:
            stack.append(next(iter(nodes)))
        
        path = []
        
        while stack:
            node = stack[-1]
            if graph[node]:
                next_node = graph[node].pop()
                stack.append(next_node)
            else:
                stack.pop()
                path.append(node)
        
        if not path:
            return []
        
        edges = []
        for i in range(len(path)-1):
            edges.append([path[i], path[i+1]])
        
        return edges