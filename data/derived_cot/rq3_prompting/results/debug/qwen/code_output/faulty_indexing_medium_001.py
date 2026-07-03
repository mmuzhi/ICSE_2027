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
        
        def checkReverse(ans):
            l, r = 0, len(ans) - 1
            while l < r:
                ans[l], ans[r] = ans[r], ans[l]
                l += 1
                r -= 1
            return ans
        
        q = [root]
        ans = []
        while q:
            level = []
            for i in range(len(q)):
                curr = q.pop(0)
                level.append(curr.val)
                if curr.left:
                    q.append(curr.left)
                if curr.right:
                    q.append(curr.right)
            ans.append(level)
        return checkReverse(ans)