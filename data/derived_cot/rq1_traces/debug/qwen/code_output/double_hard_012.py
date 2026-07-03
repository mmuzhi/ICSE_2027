class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def insert(root, val):
    if root is None:
        return Node(val)
    if val < root.val:
        root.left = insert(root.left, val)
    else:
        root.right = insert(root.right, val)
    return root

def remove(root, val):
    if root is None:
        return None
    if val < root.val:
        root.left = remove(root.left, val)
    elif val > root.val:
        root.right = remove(root.right, val)
    else:
        if root.left is None and root.right is None:
            return None
        elif root.left is None:
            return root.right
        elif root.right is None:
            return root.left
        else:
            temp = root.right
            while temp.left:
                temp = temp.left
            root.val = temp.val
            root.right = remove(root.right, temp.val)
    return root

def size(node):
    if node is None:
        return 0
    return 1 + size(node.left) + size(node.right)

def get(root, k):
    if root is None:
        return None
    left_size = size(root.left) if root.left else 0
    if left_size + 1 == k:
        return root.val
    elif k <= left_size:
        return get(root.left, k)
    else:
        return get(root.right, k - left_size - 1)

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        tree = None
        ans = []
        for i, x in enumerate(nums):
            tree = insert(tree, x)
            if i >= k:
                tree = remove(tree, nums[i - k])
            if i >= k - 1:
                if k % 2 == 1:
                    ans.append(get(tree, k // 2 + 1))
                else:
                    ans.append((get(tree, k // 2) + get(tree, k // 2 + 1)) / 2)
        return ans