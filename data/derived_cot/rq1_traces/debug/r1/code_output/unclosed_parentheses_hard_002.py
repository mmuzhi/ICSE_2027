import random
from typing import List

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        tree = None
        ans = []
        for i, x in enumerate(nums):
            tree = insert(tree, x)
            if size(tree) > k:
                tree = remove(tree, nums[i - k])
            if size(tree) == k:
                if k % 2 == 1:
                    ans.append(get(tree, k // 2 + 1))
                else:
                    ans.append((get(tree, k // 2) + get(tree, k // 2 + 1)) / 2)
        return ans

class Node:
    __slots__ = ['val', 'count', 'weight', 'size', 'left', 'right']
    def __init__(self, val):
        self.val = val
        self.count = 1
        self.weight = random.random()
        self.size = 1
        self.left = self.right = None

def touch(root):
    if not root:
        return
    root.size = root.count + size(root.left) + size(root.right)

def size(root):
    return root.size if root else 0

def insert(root, val):
    if not root:
        return Node(val)
    if val < root.val:
        root.left = insert(root.left, val)
        if root.left.weight > root.weight:
            root = rotate_right(root)
    elif val > root.val:
        root.right = insert(root.right, val)
        if root.right.weight > root.weight:
            root = rotate_left(root)
    else:
        root.count += 1
    touch(root)
    return root

def rotate_right(root):
    new_root = root.left
    root.left = new_root.right
    new_root.right = root
    touch(root)
    touch(new_root)
    return new_root

def rotate_left(root):
    new_root = root.right
    root.right = new_root.left
    new_root.left = root
    touch(root)
    touch(new_root)
    return new_root

def remove(root, val):
    if not root:
        return None
    if val < root.val:
        root.left = remove(root.left, val)
    elif val > root.val:
        root.right = remove(root.right, val)
    else:
        if root.count > 1:
            root.count -= 1
        else:
            if not root.left and not root.right:
                return None
            elif not root.left:
                return root.right
            elif not root.right:
                return root.left
            else:
                if root.left.weight > root.right.weight:
                    root = rotate_right(root)
                    root.right = remove(root.right, val)
                else:
                    root = rotate_left(root)
                    root.left = remove(root.left, val)
    touch(root)
    return root

def get(root, k):
    while True:
        left_size = size(root.left)
        if k <= left_size:
            root = root.left
        elif k <= left_size + root.count:
            return root.val
        else:
            k -= left_size + root.count
            root = root.right