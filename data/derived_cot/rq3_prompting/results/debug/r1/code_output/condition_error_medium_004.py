from typing import List

class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        n = len(grid)
        if n == 0:
            return None
        return self.buildTree(grid, 0, n, 0, n)

    def buildTree(self, grid: List[List[int]], rs: int, re: int, cs: int, ce: int) -> 'Node':
        # Base case: 1x1 cell -> leaf
        if re - rs == 1 and ce - cs == 1:
            return Node(grid[rs][cs], True, None, None, None, None)

        mid_r = (rs + re) // 2
        mid_c = (cs + ce) // 2

        topLeft = self.buildTree(grid, rs, mid_r, cs, mid_c)
        topRight = self.buildTree(grid, rs, mid_r, mid_c, ce)
        bottomLeft = self.buildTree(grid, mid_r, re, cs, mid_c)
        bottomRight = self.buildTree(grid, mid_r, re, mid_c, ce)

        # If all four children are leaves with the same value, merge into a leaf
        if (topLeft.isLeaf and topRight.isLeaf and bottomLeft.isLeaf and bottomRight.isLeaf and
            topLeft.val == topRight.val == bottomLeft.val == bottomRight.val):
            return Node(topLeft.val, True, None, None, None, None)
        else:
            return Node(topLeft.val, False, topLeft, topRight, bottomLeft, bottomRight)