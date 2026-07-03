class Solution:
    def medianSlidingWindow(self, nums: List[int], k: int) -> List[float]:
        class Node:
            __slots__ = ('val', 'left', 'right', 'size')
            def __init__(self, val):
                self.val = val
                self.left = self.right = None
                self.size = 1

        def insert(root, val):
            if not root:
                return Node(val)
            if val < root.val:
                root.left = insert(root.left, val)
            else:
                root.right = insert(root.right, val)
            root.size += 1
            return root

        def remove(root, val):
            if not root:
                return None
            if val < root.val:
                root.left = remove(root.left, val)
                root.size -= 1
            elif val > root.val:
                root.right = remove(root.right, val)
                root.size -= 1
            else:
                if not root.left and not root.right:
                    return None
                elif not root.left:
                    return root.right
                elif not root.right:
                    return root.left
                successor = root.right
                while successor.left:
                    successor = successor.left
                root.val = successor.val
                root.right = remove(root.right, successor.val)
                root.size -= 1
            return root

        def size(root):
            if not root:
                return 0
            return root.size

        def get_kth(root, k):
            if not root:
                return None
            left_size = size(root.left) if root.left else 0
            if k == left_size + 1:
                return root.val
            elif k < left_size + 1:
                return get_kth(root.left, k)
            else:
                return get_kth(root.right, k - left_size - 1)

        tree = None
        ans = []
        n = len(nums)
        for i in range(n):
            tree = insert(tree, nums[i])
            if i >= k:
                tree = remove(tree, nums[i-k])
            if size(tree) == k:
                if k % 2 == 1:
                    median = get_kth(tree, k//2+1)
                    ans.append(median)
                else:
                    a = get_kth(tree, k//2)
                    b = get_kth(tree, k//2+1)
                    ans.append((a + b) / 2.0)
        return ans