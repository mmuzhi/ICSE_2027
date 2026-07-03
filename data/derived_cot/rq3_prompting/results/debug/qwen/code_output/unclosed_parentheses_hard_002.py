from typing import List
import random

class Node:
    __slots__ = ['val', 'count', 'weight', 'size', 'left', 'right']
    def __init__(self, val):
        self.val = val
        self.count = 1
        self.weight = random.random()
        self.size = 1
        self.left = None
        self.right = None

def update_size(node):
    if node is None:
        return 0
    left_size = node.left.size if node.left else 0
    right_size = node.right.size if node.right else 0
    node.size = node.count + left_size + right_size

def insert(root, val):
    if not root:
        return Node(val)
    if val == root.val:
        root.count += 1
        update_size(root)
        return root
    elif val < root.val:
        root.left = insert(root.left, val)
        if root.left.weight > root.weight:
            root = right_rotate(root)
    else:
        root.right = insert(root.right, val)
        if root.right.weight > root.weight:
            root = left_rotate(root)
    update_size(root)
    return root

def remove(root, val):
    if not root:
        return None
    if val == root.val:
        if root.count > 1:
            root.count -= 1
            update_size(root)
            return root
        if not root.left and not root.right:
            return None
        elif not root.left:
            return root.right
        elif not root.right:
            return root.left
        else:
            temp = root.right
            while temp.left:
                temp = temp.left
            root.val = temp.val
            root.count = 1
            root = remove(root, root.val)
            update_size(root)
            return root
    elif val < root.val:
        root.left = remove(root.left, val)
        update_size(root)
        return root
    else:
        root.right = remove(root.right, val)
        update_size(root)
        return root

def get(root, k):
    if not root:
        return None
    left_size = root.left.size if root.left else 0
    if k <= left_size:
        return get(root.left, k)
    elif k <= left_size + root.count:
        return root.val
    else:
        return get(root.right, k - left_size - root.count)

def left_rotate(x):
    y = x.right
    x.right = y.left
    y.left = x
    update_size(x)
    update_size(y)
    return y

def right_rotate(x):
    y = x.left
    x.left = y.right
    y.right = x
    update_size(x)
    update_size(y)
    return y

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        root = None
        ans = []
        for i, x in enumerate(nums):
            root = insert(root, x)
            if i >= k:
                root = remove(root, nums[i - k + 1])
            if i >= k - 1:
                if k % 2 == 1:
                    ans.append(get(root, (k + 1) // 2))
                else:
                    mid1 = get(root, k // 2)
                    mid2 = get(root, k // 2 + 1)
                    ans.append((mid1 + mid2) / 2.0)
        return ans