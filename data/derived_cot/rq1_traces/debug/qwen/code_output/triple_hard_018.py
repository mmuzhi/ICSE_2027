class Solution:
    class Node:
        __slots__ = ('val', 'count', 'left', 'right', 'size')
        def __init__(self, val):
            self.val = val
            self.count = 1
            self.left = None
            self.right = None
            self.size = 1

    def insert(self, root, val):
        if root is None:
            return self.Node(val)
        if val == root.val:
            root.count += 1
            root.size += 1
            return root
        if val < root.val:
            root.left = self.insert(root.left, val)
        else:
            root.right = self.insert(root.right, val)
        root.size = 1 + (root.left.size if root.left else 0) + (root.right.size if root.right else 0)
        return root

    def remove(self, root, val):
        if root is None:
            return None
        if val == root.val:
            root.count -= 1
            root.size -= 1
            return root
        if val < root.val:
            root.left = self.remove(root.left, val)
        else:
            root.right = self.remove(root.right, val)
        root.size = 1 + (root.left.size if root.left else 0) + (root.right.size if root.right else 0)
        return root

    def size(self, root):
        if root is None:
            return 0
        return root.size

    def get(self, root, k):
        if root is None:
            return None
        left_size = root.left.size if root.left else 0
        if k <= left_size:
            return self.get(root.left, k)
        elif k == left_size + 1:
            return root.val
        else:
            return self.get(root.right, k - left_size - 1)

    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        tree = None
        ans = []
        n = len(nums)
        for i, x in enumerate(nums):
            tree = self.insert(tree, x)
            if i >= k:
                tree = self.remove(tree, nums[i - k])
            if i >= k - 1:
                if k % 2 == 1:
                    median = self.get(tree, (k // 2) + 1)
                    ans.append(median)
                else:
                    left_val = self.get(tree, k // 2)
                    right_val = self.get(tree, k // 2 + 1)
                    ans.append((left_val + right_val) / 2.0)
        return ans