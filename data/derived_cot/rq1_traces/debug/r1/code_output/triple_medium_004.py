# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
import collections

class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        if not root:
            return -1
        dq = collections.deque([root])
        level_sums = []
        while dq:
            level_sum = 0
            level_length = len(dq)
            for _ in range(level_length):
                node = dq.popleft()
                level_sum += node.val
                if node.left:
                    dq.append(node.left)
                if node.right:
                    dq.append(node.right)
            level_sums.append(level_sum)
        level_sums.sort(reverse=True)
        return level_sums[k-1] if k <= len(level_sums) else -1