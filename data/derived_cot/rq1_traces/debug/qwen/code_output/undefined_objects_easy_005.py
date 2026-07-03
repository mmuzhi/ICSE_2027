# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        freq = {}
        if root is None:
            return []
        
        stack = [root]
        while stack:
            curr = stack.pop()
            freq[curr.val] = freq.get(curr.val, 0) + 1
            if curr.left:
                stack.append(curr.left)
            if curr.right:
                stack.append(curr.right)
        
        max_cnt = 0
        for count in freq.values():
            if count > max_cnt:
                max_cnt = count
        
        ans = [num for num, cnt in freq.items() if cnt == max_cnt]
        return ans