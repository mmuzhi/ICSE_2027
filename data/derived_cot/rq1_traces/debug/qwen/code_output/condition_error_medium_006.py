import collections

class Solution:
    def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
        if not root:
            return None
        queue = collections.deque([(root, 0)])
        max_depth = -1
        ans = None
        while queue:
            node, depth = queue.popleft()
            if depth > max_depth:
                max_depth = depth
                ans = node.val
            if node.left:
                queue.append((node.left, depth + 1))
            if node.right:
                queue.append((node.right, depth + 1))
        return ans