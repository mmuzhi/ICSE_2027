class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None
        self.count = 1

class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        tree = None
        ans = []
        
        def insert(node, x):
            if node is None:
                return Node(x)
            if x == node.val:
                node.count += 1
                return node
            elif x < node.val:
                node.left = insert(node.left, x)
            else:
                node.right = insert(node.right, x)
            return node
        
        def remove(node, x):
            if node is None:
                return None
            if x == node.val:
                node.count -= 1
                if node.count == 0:
                    return None
                return node
            elif x < node.val:
                node.left = remove(node.left, x)
            else:
                node.right = remove(node.right, x)
            return node
        
        def get(node, k):
            if node is None:
                return None
            left_size = size(node.left) if node.left else 0
            if k <= left_size:
                return get(node.left, k)
            elif k == left_size + 1:
                return node.val
            else:
                return get(node.right, k - left_size - 1)
        
        def size(node):
            if node is None:
                return 0
            return node.count + size(node.left) + size(node.right)
        
        for i, x in enumerate(nums):
            tree = insert(tree, x)
            if i >= k - 1 and size(tree) > k:
                tree = remove(tree, nums[i - k + 1])
            if size(tree) == k:
                if k % 2 == 1:
                    ans.append(get(tree, k // 2 + 1))
                else:
                    median = (get(tree, k // 2) + get(tree, k // 2 + 1)) / 2.0
                    ans.append(median)
        
        return ans