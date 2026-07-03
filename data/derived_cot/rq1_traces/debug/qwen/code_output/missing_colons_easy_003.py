class Solution:
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        if root is None:
            return []
        
        freq = {}
        stack = [root]
        while stack:
            curr = stack.pop()
            freq[curr.val] = freq.get(curr.val, 0) + 1
            if curr.right:
                stack.append(curr.right)
            if curr.left:
                stack.append(curr.left)
                
        max_cnt = 0
        ans = []
        for num, cnt in freq.items():
            if cnt > max_cnt:
                max_cnt = cnt
                ans = [num]
            elif cnt == max_cnt:
                ans.append(num)
        return ans