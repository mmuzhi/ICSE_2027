from typing import List

class Node:
    __slots__ = ['val', 'left', 'right', 'size']
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.size = 1

def insert(root, val):
    if root is None:
        return Node(val)
    if val < root.val:
        root.left = insert(root.left, val)
    else:
        root.right = insert(root.right, val)
    root.size += 1
    return root

def remove(root, val):
    if root is None:
        return None
    if val == root.val:
        if root.left is None:
            return root.right
        if root.right is None:
            return root.left
        temp = root.right
        while temp.left:
            temp = temp.left
        root.val = temp.val
        root.right = remove(root.right, temp.val)
        return root
    elif val < root.val:
        root.left = remove(root.left, val)
    else:
        root.right = remove(root.right, val)
    root.size -= 1
    return root

def size(root):
    return root.size if root else 0

def get(root, k):
    if not root:
        return None
    left_size = size(root.left) if root.left else 0
    if k <= left_size:
        return get(root.left, k)
    elif k == left_size + 1:
        return root.val
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
                    a = get(tree, k // 2)
                    b = get(tree, k // 2 + 1)
                    ans.append((a + b) / 2.0)
        return ans