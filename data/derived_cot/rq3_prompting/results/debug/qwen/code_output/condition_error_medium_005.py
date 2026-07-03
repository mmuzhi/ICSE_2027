# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        if not inorder or not postorder:
            return None
        
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        
        def treeHelper(left, right, left_post, right_post):
            if left > right or left_post > right_post:
                return None
            
            node_val = postorder[right_post]
            root = TreeNode(node_val)
            
            inorder_index = inorder_map[node_val]
            
            len_left = inorder_index - left
            root.left = treeHelper(left, inorder_index-1, left_post, left_post+len_left-1)
            
            len_right = right - inorder_index
            root.right = treeHelper(inorder_index+1, right, left_post+len_left, right_post-1)
            
            return root
        
        return treeHelper(0, len(inorder)-1, 0, len(postorder)-1)