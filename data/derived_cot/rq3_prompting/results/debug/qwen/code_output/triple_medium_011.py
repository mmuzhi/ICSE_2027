from collections import deque

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def levelOrderBottom(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        queue = deque([root])
        lst = []
        while queue:
            levels = []
            level_size = len(queue)
            for _ in range(level_size):
                node = queue.popleft()
                if node:
                    levels.append(node.val)
                    queue.append(node.left)
                    queue.append(node.right)
            if levels:
                lst.append(levels)
        return lst[::-1]