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
            # leaf node: single cell
            return Node(grid[rs][cs], True, None, None, None, None)

        next_level = level // 2
        # top-left: rows rs to rs+next_level, columns cs to cs+next_level
        tl = self.buildTree(grid, rs, rs + next_level, cs, cs + next_level, next_level)
        # top-right: rows rs to rs+next_level, columns cs+next_level to ce
        tr = self.buildTree(grid, rs, rs + next_level, cs + next_level, ce, next_level)
        # bottom-left: rows rs+next_level to re, columns cs to cs+next_level
        bl = self.buildTree(grid, rs + next_level, re, cs, cs + next_level, next_level)
        # bottom-right: rows rs+next_level to re, columns cs+next_level to ce
        br = self.buildTree(grid, rs + next_level, re, cs + next_level, ce, next_level)

        if tl.isLeaf and tr.isLeaf and bl.isLeaf and br.isLeaf and tl.val == tr.val == bl.val == br.val:
            new_node = Node(tl.val, True, None, None, None, None)
        else:
            new_node = Node(tl.val, False, tl, tr, bl, br)

        return new_node