from typing import Optional
import collections

class Solution:
    def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
        if not root:
            return None
        
        q = collections.deque()
        q.append((root, 0))
        max_level = -1
        leftmost_value = None
        
        while q:
            node, level = q.popleft()
            if level > max_level:
                max_level = level
                leftmost_value = node.val
            if node.left:
                q.append((node.left, level + 1))
            if node.right:
                q.append((node.right, level + 1))
                
        return leftmost_value