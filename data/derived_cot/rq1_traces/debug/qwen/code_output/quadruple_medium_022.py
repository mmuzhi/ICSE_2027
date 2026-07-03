class Solution:
    def smallestString(self, s: str) -> str:
        ans = []
        for char in s:
            if char == 'z':
                ans.append('y')
            else:
                ans.append(char)
        return ''.join(ans)