from typing import Optional, List

class Solution:
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        
        def bfs(freq):
            queue = [root]
            while queue:
                curr = queue.pop()
                if curr.left:
                    queue.append(curr.left)
                if curr.right:
                    queue.append(curr.right)
                freq[curr.val] = freq.get(curr.val, 0) + 1
        
        freq = {}
        bfs(freq)
        items = list(freq.items())
        ans = []
        max_cnt = 0
        
        for num, cnt in items:
            if cnt > max_cnt:
                max_cnt = cnt
        
        for num, cnt in items:
            if cnt == max_cnt:
                ans.append(num)
        return ans