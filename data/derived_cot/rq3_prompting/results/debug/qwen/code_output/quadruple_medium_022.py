class Solution:
    def smallestString(self, s: str) -> str:
        ans = []
        for char in s:
            if char == 'a':
                ans.append('a')
            else:
                ans.append(chr(ord(char) - 1))
        return ''.join(ans)