from collections import deque

class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        if not root:
            return -1
        
        dq = deque([root])
        level_sums = []
        
        while dq:
            current_sum = 0
            for _ in range(len(dq)):
                node = dq.popleft()
                current_sum += node.val
                if node.left:
                    dq.append(node.left)
                if node.right:
                    dq.append(node.right)
            level_sums.append(current_sum)
        
        level_sums.sort(reverse=True)
        
        return level_sums[k-1] if len(level_sums) >= k else -1