from typing import Optional
import collections

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        dq = collections.deque([root])
        sums = []
        while dq:
            current_sum = 0
            level_size = len(dq)
            for _ in range(level_size):
                node = dq.popleft()
                current_sum += node.val
                if node.left:
                    dq.append(node.left)
                if node.right:
                    dq.append(node.right)
            sums.append(current_sum)
        sums.sort(reverse=True)
        if len(sums) < k:
            return -1
        return sums[k-1]