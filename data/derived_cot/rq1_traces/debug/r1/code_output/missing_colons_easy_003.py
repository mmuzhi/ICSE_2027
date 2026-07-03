class Solution:
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        def dfs(freq):
            stack = [root]
            while stack:
                curr = stack.pop()
                if curr.left:
                    stack.append(curr.left)
                if curr.right:
                    stack.append(curr.right)
                freq[curr.val] = freq.get(curr.val, 0) + 1

        if not root:
            return []
        
        freq = {}
        dfs(freq)
        
        max_cnt = max(freq.values())
        ans = [num for num, cnt in freq.items() if cnt == max_cnt]
        
        return ans