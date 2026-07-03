def tsum(root):
    if root is None:
        return 0
    x = root.val + tsum(root.left) + tsum(root.right)
    return x

def fun(root, sm, mx):
    if root is None:
        return 0
    a = fun(root.left, sm, mx)
    b = fun(root.right, sm, mx)
    current_sum = a + b + root.val
    candidate = current_sum * (sm - current_sum)
    if candidate > mx[0]:
        mx[0] = candidate
    return current_sum

class Solution:
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        sm = tsum(root)
        mx = [0]
        fun(root, sm, mx)
        return mx[0] % (10**9 + 7)