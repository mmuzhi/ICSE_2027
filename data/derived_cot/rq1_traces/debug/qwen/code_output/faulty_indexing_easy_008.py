"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children

class Solution:
    def maxDepth(self, root: 'Node') -> int:
        if root is None:
            return 0
        depth = 0
        queue = [root]
        while queue:
            depth += 1
            next_queue = []
            for node in queue:
                for child in node.children:
                    next_queue.append(child)
            queue = next_queue
        return depth