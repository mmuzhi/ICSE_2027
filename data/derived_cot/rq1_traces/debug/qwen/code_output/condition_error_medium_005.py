# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        n = len(inorder)
        
        def treeHelper(left, right, post_start, post_end):
            if left > right:
                return None
                
            root_val = postorder[post_end]
            root = TreeNode(root_val)
            inorder_index = inorder_map[root_val]
            
            left_tree_size = inorder_index - left
            right_tree_size = right - inorder_index
            
            root.left = treeHelper(left, inorder_index-1, post_start, post_start+left_tree_size-1)
            root.right = treeHelper(inorder_index+1, right, post_start+left_tree_size, post_end-1)
            
            return root
        
        return treeHelper(0, n-1, 0, n-1)