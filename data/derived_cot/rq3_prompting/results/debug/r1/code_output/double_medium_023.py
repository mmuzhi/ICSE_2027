from typing import List

class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        level = len(grid)
        root = None
        if level >= 1:
            root = self.buildTree(grid, 0, level, 0, level, level)
        return root

    def buildTree(self, grid, rs, re, cs, ce, level):
        if level == 1:
            # leaf node: value is True if grid cell is 1, else False
            return Node(grid[rs][cs] == 1, True, None, None, None, None)

        next_level = level // 2
        # quadrants: top-left, top-right, bottom-left, bottom-right
        tl = self.buildTree(grid, rs, rs + next_level, cs, cs + next_level, next_level)
        tr = self.buildTree(grid, rs, rs + next_level, cs + next_level, ce, next_level)
        bl = self.buildTree(grid, rs + next_level, re, cs, cs + next_level, next_level)
        br = self.buildTree(grid, rs + next_level, re, cs + next_level, ce, next_level)

        if (tl.isLeaf and tr.isLeaf and bl.isLeaf and br.isLeaf and
            tl.val == tr.val == bl.val == br.val):
            new_node = Node(tl.val, True, None, None, None, None)
        else:
            new_node = Node(tl.val, False, tl, tr, bl, br)

        return new_node