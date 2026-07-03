class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        level = len(grid)
        if level == 0:
            return None
        root = None
        if level >= 1:
            root = self.buildTree(grid, 0, level, 0, level, level)
        return root
        
    def buildTree(self, grid, rs, re, cs, ce, level):
        if level == 1:
            return Node(grid[rs][cs], True, None, None, None, None)
        
        half = level // 2
        tl = self.buildTree(grid, rs, rs+half, cs, cs+half, half)
        tr = self.buildTree(grid, rs, rs+half, cs+half, cs+level, half)
        bl = self.buildTree(grid, rs+half, re, cs, cs+half, half)
        br = self.buildTree(grid, rs+half, re, cs+half, cs+level, half)
        
        if tl.isLeaf and tr.isLeaf and bl.isLeaf and br.isLeaf:
            if tl.val == tr.val == bl.val == br.val:
                new_node = Node(tl.val, True, None, None, None, None)
            else:
                new_node = Node(tl.val, False, tl, tr, bl, br)
        else:
            new_node = Node(tl.val, False, tl, tr, bl, br)
            
        return new_node