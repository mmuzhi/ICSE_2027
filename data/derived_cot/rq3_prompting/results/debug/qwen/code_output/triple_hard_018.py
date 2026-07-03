class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        tree = None
        ans = []
        for i, x in enumerate(nums):
            tree = insert(tree, x)
            if size(tree) > k:
                tree = remove(tree, nums[i - k + 1])
            if size(tree) == k:
                if k % 2 == 1:
                    ans.append(get(tree, k // 2 + 1))
                else:
                    ans.append((get(tree, k // 2) + get(tree, k // 2 + 1)) / 2)
        return ans

class Node:
    __slots__ = ('val', 'left', 'right', 'size')
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.size = 1

def size(node):
    if node is None:
        return 0
    return node.size

def insert(node, val):
    if node is None:
        return Node(val)
    if val < node.val:
        node.left = insert(node.left, val)
    else:
        node.right = insert(node.right, val)
    node.size = size(node.left) + size(node.right) + 1
    return node

def remove(node, val):
    if node is None:
        return None
    if val < node.val:
        node.left = remove(node.left, val)
    elif val > node.val:
        node.right = remove(node.right, val)
    else:
        if node.left is None:
            return node.right
        elif node.right is None:
            return node.left
        else:
            temp = min_node(node.right)
            node.val = temp.val
            node.right = remove(node.right, temp.val)
    node.size = size(node.left) + size(node.right) + 1
    return node

def min_node(node):
    while node.left is not None:
        node = node.left
    return node

def get(node, rank):
    while node:
        left_size = size(node.left)
        if left_size + 1 == rank:
            return node.val
        elif left_size >= rank:
            node = node.left
        else:
            node = node.right
            rank -= left_size + 1
    return None