class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        n = len(grid)
        if n == 0:
            return None
        return self.buildTree(grid, 0, n, 0, n, n)
        
    def buildTree(self, grid, rs, re, cs, ce, level):
        if level == 1:
            return Node(grid[rs][cs], True, None, None, None, None)
        
        next_level = level // 2
        mid_row = rs + next_level
        mid_col = cs + next_level
        tl = self.buildTree(grid, rs, mid_row, cs, mid_col, next_level)
        tr = self.buildTree(grid, rs, mid_row, mid_col, ce, next_level)
        bl = self.buildTree(grid, mid_row, re, cs, mid_col, next_level)
        br = self.buildTree(grid, mid_row, re, mid_col, ce, next_level)
        
        if tl.isLeaf and tr.isLeaf and bl.isLeaf and br.isLeaf and tl.val == tr.val == bl.val == br.val:
            return Node(tl.val, True, None, None, None, None)
        else:
            return Node(tl.val, False, tl, tr, bl, br)