# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        if root is None:
            return []
        
        def dfs(freq):
            stack = [root]
            while stack:
                curr = stack.pop()
                freq.setdefault(curr.val, 0)
                freq[curr.val] += 1
                if curr.left:
                    stack.append(curr.left)
                if curr.right:
                    stack.append(curr.right)
        
        freq = {}
        dfs(freq)
        if not freq:
            return []
        max_cnt = max(freq.values())
        ans = [num for num, cnt in freq.items() if cnt == max_cnt]
        return ans