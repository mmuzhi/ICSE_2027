class Solution:
    def smallestString(self, s: str) -> str:
        s = list(s)
        n = len(s)
        # Find first non-'a' character
        i = 0
        while i < n and s[i] == 'a':
            i += 1
        if i == n:
            # All characters are 'a', change the last one to 'z'
            s[-1] = 'z'
            return ''.join(s)
        # Decrement consecutive non-'a' characters
        while i < n and s[i] != 'a':
            s[i] = chr(ord(s[i]) - 1)
            i += 1
        return ''.join(s)