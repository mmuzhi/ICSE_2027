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

def touch(root):
    if root is None:
        return
    root.size = root.count + size(root.left) + size(root.right)

def size(root):
    if root is None:
        return 0
    return root.size

def rotate_right(p):
    q = p.left
    p.left = q.right
    q.right = p
    touch(p)
    touch(q)
    return q

def rotate_left(p):
    q = p.right
    p.right = q.left
    q.left = p
    touch(p)
    touch(q)
    return q

def insert(root, val):
    if root is None:
        return Node(val)
    if val < root.val:
        root.left = insert(root.left, val)
        if root.left.weight < root.weight:
            root = rotate_right(root)
    elif val > root.val:
        root.right = insert(root.right, val)
        if root.right.weight < root.weight:
            root = rotate_left(root)
    else:
        root.count += 1
    touch(root)
    return root

def remove(root, val):
    if root is None:
        return None
    if val < root.val:
        root.left = remove(root.left, val)
    elif val > root.val:
        root.right = remove(root.right, val)
    else:
        if root.count > 1:
            root.count -= 1
        else:
            if root.left is None:
                return root.right
            if root.right is None:
                return root.left
            if root.left.weight < root.right.weight:
                root = rotate_right(root)
                root.right = remove(root.right, val)
            else:
                root = rotate_left(root)
                root.left = remove(root.left, val)
    touch(root)
    return root

def get_kth(root, k):
    # k is 1-indexed
    left_size = size(root.left)
    if k <= left_size:
        return get_kth(root.left, k)
    elif k <= left_size + root.count:
        return root.val
    else:
        return get_kth(root.right, k - left_size - root.count)

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
                    ans.append(float(get_kth(tree, k // 2 + 1)))
                else:
                    left = get_kth(tree, k // 2)
                    right = get_kth(tree, k // 2 + 1)
                    ans.append((left + right) / 2.0)
        return ans