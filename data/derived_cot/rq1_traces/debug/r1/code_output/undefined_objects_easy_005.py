# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        def dfs(freq):
            stack = [root]
            while stack:
                curr = stack.pop()
                if curr.left:
                    stack.append(curr.left)
                if curr.right:
                    stack.append(curr.right)
                freq[curr.val] = freq.get(curr.val, 0) + 1
        
        if not root:
            return []
        
        freq = {}
        dfs(freq)
        
        max_count = max(freq.values())
        return [num for num, count in freq.items() if count == max_count]