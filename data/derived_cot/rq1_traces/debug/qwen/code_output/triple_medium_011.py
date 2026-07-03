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
        queue = deque()
        queue.append(root)
        lst = []
        while queue:
            level_size = len(queue)
            levels = []
            for i in range(level_size):
                tmp = queue.popleft()
                if tmp:
                    levels.append(tmp.val)
                    queue.append(tmp.left)
                    queue.append(tmp.right)
            if levels:
                lst.append(levels)
        return lst[::-1]